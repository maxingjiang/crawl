/*
 * gumboServer.cpp
 *
 *  Created on: Jul 5, 2016
 *      Author: root
 */

#include "gumboServer.h"

CRuleArgs::CRuleArgs()
{
	this->m_tag = GUMBO_TAG_A;
	this->m_attributes.clear();
	this->m_value.clear();
	this->m_text.clear();
}

CRuleArgs::~CRuleArgs()
{
	this->m_tag = GUMBO_TAG_A;
	this->m_attributes.clear();
	this->m_value.clear();
	this->m_text.clear();
}

vector<string> CgumboServer::getUrlLink(string &responsedata, string &keyword)
{
	GumboOutput* output = gumbo_parse(responsedata.c_str());
	vector<string> links;
	links.clear();
	if(!output)
	{
		return links;
	 }
	search_for_links(output->root, keyword, links);
	gumbo_destroy_output(&kGumboDefaultOptions, output);
	return links;
}

void CgumboServer::search_for_links(GumboNode* node, string &keyword, vector<string> &links)
{
	if (node->type != GUMBO_NODE_ELEMENT)
	{
		return;
	}
	GumboAttribute* href;
	if (node->v.element.tag == GUMBO_TAG_A &&
	(href = gumbo_get_attribute(&node->v.element.attributes, "href")))
	{
		string src = href->value;
		//cout<<"src: "<<src<<endl;
		int pos = src.find(keyword.c_str(), 0);
		//cout<<"len: "<<strlen(href->value)<<endl;
		if(pos >= 0 && strlen(href->value) <= 512)
		{
			//std::cout <<"===use===>"<< href->value << std::endl;
			links.push_back(href->value);
		}
	}
	if (node->v.element.tag == GUMBO_TAG_IMG &&
	(href = gumbo_get_attribute(&node->v.element.attributes, "src")))
	{
		string src = href->value;
		//cout<<"========>img: "<<src<<endl;
		int pos = src.find("uploads", 0);
		if(pos >= 0)
		{
			string cmd = "echo "+src+" >> ./image.log";
			system(cmd.c_str());
		}
	}
	GumboVector* children = &node->v.element.children;
	for (unsigned int i = 0; i < children->length; ++i)
	{
		search_for_links(static_cast<GumboNode*>(children->data[i]), keyword, links);
	}
}

void CgumboServer::print_info(GumboNode *node,GumboAttribute *attr)
{
	//cout<<"========>print info: "<<endl;
	/* 获取子节点 */
	//GumboNode *ip=(GumboNode *)(&node->v.element.children)->data[0];

	/* 根据属性的值打印结果 */
	if(attr != NULL)
	{
		printf("value: %s\n",attr->value);
		string cmd = string("echo ")+attr->value+" >> ./image.log";
		system(cmd.c_str());
	}
	if(node->type == GUMBO_NODE_TEXT)
	{
		//string src = ip->v.text.text;
		//matchTemplate match;
		//match.removeSpace(src);
		//printf("len %d: %s\n\n",src.size(), src.c_str());
		//if(src.size() > 0)
		//	src.erase( remove( src.begin(), src.end(), ' ' ), src.end() );
		printf("%s\n\n",node->v.text.text);
	}
}

void CgumboServer::get_info(GumboNode *node, vector<CRuleArgs> &deepRule, unsigned int num)
{
	GumboVector *children;
	GumboAttribute *attr;
	if (deepRule.size() <= 0)
		return ;
	if(node->type != GUMBO_NODE_ELEMENT)
		return;
	/* 获取当前节点class属性 */
	//cout<<num<<" => tag: "<<node->v.element.tag<<endl;

	if(num == deepRule.size() - 1 && node->v.element.tag == deepRule[num].m_tag)
	{
		//cout<<num<<" => tag: "<<node->v.element.tag<<endl;
		if((attr=gumbo_get_attribute(&node->v.element.attributes,deepRule[num].m_attributes.c_str())) != NULL)
			print_info(node,attr);
		else
			print_info(node, NULL);
	}

	children = &node->v.element.children;
	if(node->v.element.tag == deepRule[num].m_tag)
	{
		for(unsigned i = 0; i < children->length; ++i)
		{
			//GumboNode *childnode = (GumboNode*)children->data[i];
			if(0)
			{
				if(node->type != GUMBO_NODE_ELEMENT)
					continue ;
				attr=gumbo_get_attribute(&node->v.element.attributes,deepRule[num].m_attributes.c_str());

				if(attr != NULL)
				{
					//cout<<"attr->value: "<<attr->value<<endl;
				}
				if(attr != NULL && strcmp(attr->value, deepRule[num].m_value.c_str()) == 0)
				{
					//cout<< "GUMBO_TAG_DL tag: "<<deepRule[num].m_tag<<endl;
					get_info((GumboNode*)children->data[i], deepRule, num + 1);
				}
			}
			else
			{
				get_info((GumboNode*)children->data[i], deepRule, num + 1);
			}
		}
	}
	/* 查找所有标签 */
	//for(unsigned i=0;i < children->length;++i)
	//	get_info((GumboNode*)children->data[i],GUMBO_TAG_DL, deepRule, num + 1);
}

void CgumboServer::getAllInfo(string &responsedata)
{
	CreadFile file;
	vector<CRuleArgs> CRuleArgss;
	string searchword = "alphaGo";
	vector<string> colorRuleStrings = file.getFileString("/root/CCrawl_Server/GumboServer/tianya.colorcontent.rule");
	CRuleArgss = getRuleArgs("/root/CCrawl_Server/GumboServer/tianya.conf");
	if(colorRuleStrings.size() >= 1)
	{
		ReplaceStr(colorRuleStrings[0], "XXX", searchword.c_str(), 1);
		ReplaceStr(responsedata, colorRuleStrings[0].c_str(), searchword.c_str(), 1);
		//cout<<colorRuleStrings[0]<<endl;
		//cout<<responsedata<<endl;
	}
	GumboOutput *output;
	output=gumbo_parse(responsedata.c_str());
	if(!output)
	{
		return ;
	 }
	 /* 获取我们想要的内容 <dt>*/
	get_info(output->root, CRuleArgss, 0);

	 /* 释放资源 */
	 gumbo_destroy_output(&kGumboDefaultOptions,output);
}

vector<CRuleArgs> CgumboServer::getRuleArgs(string rulefile)
{
	CreadFile file;
	vector<CRuleArgs> CRuleArgss;
	CRuleArgss.clear();
	vector<string> FileStrings = file.getFileString(rulefile);
	for(unsigned int i = 0; i < FileStrings.size(); ++i)
	{
		CRuleArgs arg;
		vector<string> split = file.split(FileStrings[i], "---");
		if(split.size() == 4)
		{
			arg.m_tag = getTag(split[0]);
			arg.m_attributes = split[1];
			arg.m_value = split[2];
			arg.m_text = split[3];
		}
		CRuleArgss.push_back(arg);
	}
	return CRuleArgss;
}

GumboTag CgumboServer::getTag(const string &strtag)
{
	GumboTag tag;
	if(strtag == "GUMBO_TAG_HTML")
	    tag = GUMBO_TAG_HTML;
	else if(strtag == "GUMBO_TAG_HEAD")
	    tag = GUMBO_TAG_HEAD;
	else if(strtag == "GUMBO_TAG_TITLE")
	    tag = GUMBO_TAG_TITLE;
	else if(strtag == "GUMBO_TAG_BASE")
	    tag = GUMBO_TAG_BASE;
	else if(strtag == "GUMBO_TAG_LINK")
	    tag = GUMBO_TAG_LINK;
	else if(strtag == "GUMBO_TAG_META")
	    tag = GUMBO_TAG_META;
	else if(strtag == "GUMBO_TAG_STYLE")
	    tag = GUMBO_TAG_STYLE;
	else if(strtag == "GUMBO_TAG_SCRIPT")
	    tag = GUMBO_TAG_SCRIPT;
	else if(strtag == "GUMBO_TAG_NOSCRIPT")
	    tag = GUMBO_TAG_NOSCRIPT;
	else if(strtag == "GUMBO_TAG_TEMPLATE")
	    tag = GUMBO_TAG_TEMPLATE;
	else if(strtag == "GUMBO_TAG_BODY")
	    tag = GUMBO_TAG_BODY;
	else if(strtag == "GUMBO_TAG_ARTICLE")
	    tag = GUMBO_TAG_ARTICLE;
	else if(strtag == "GUMBO_TAG_SECTION")
	    tag = GUMBO_TAG_SECTION;
	else if(strtag == "GUMBO_TAG_NAV")
	    tag = GUMBO_TAG_NAV;
	else if(strtag == "GUMBO_TAG_ASIDE")
	    tag = GUMBO_TAG_ASIDE;
	else if(strtag == "GUMBO_TAG_H1")
	    tag = GUMBO_TAG_H1;
	else if(strtag == "GUMBO_TAG_H2")
	    tag = GUMBO_TAG_H2;
	else if(strtag == "GUMBO_TAG_H3")
	    tag = GUMBO_TAG_H3;
	else if(strtag == "GUMBO_TAG_H4")
	    tag = GUMBO_TAG_H4;
	else if(strtag == "GUMBO_TAG_H5")
	    tag = GUMBO_TAG_H5;
	else if(strtag == "GUMBO_TAG_H6")
	    tag = GUMBO_TAG_H6;
	else if(strtag == "GUMBO_TAG_HGROUP")
	    tag = GUMBO_TAG_HGROUP;
	else if(strtag == "GUMBO_TAG_HEADER")
	    tag = GUMBO_TAG_HEADER;
	else if(strtag == "GUMBO_TAG_FOOTER")
	    tag = GUMBO_TAG_FOOTER;
	else if(strtag == "GUMBO_TAG_ADDRESS")
	    tag = GUMBO_TAG_ADDRESS;
	else if(strtag == "GUMBO_TAG_P")
	    tag = GUMBO_TAG_P;
	else if(strtag == "GUMBO_TAG_HR")
	    tag = GUMBO_TAG_HR;
	else if(strtag == "GUMBO_TAG_PRE")
	    tag = GUMBO_TAG_PRE;
	else if(strtag == "GUMBO_TAG_BLOCKQUOTE")
	    tag = GUMBO_TAG_BLOCKQUOTE;
	else if(strtag == "GUMBO_TAG_OL")
	    tag = GUMBO_TAG_OL;
	else if(strtag == "GUMBO_TAG_UL")
	    tag = GUMBO_TAG_UL;
	else if(strtag == "GUMBO_TAG_LI")
	    tag = GUMBO_TAG_LI;
	else if(strtag == "GUMBO_TAG_DL")
	    tag = GUMBO_TAG_DL;
	else if(strtag == "GUMBO_TAG_DT")
	    tag = GUMBO_TAG_DT;
	else if(strtag == "GUMBO_TAG_DD")
	    tag = GUMBO_TAG_DD;
	else if(strtag == "GUMBO_TAG_FIGURE")
	    tag = GUMBO_TAG_FIGURE;
	else if(strtag == "GUMBO_TAG_FIGCAPTION")
	    tag = GUMBO_TAG_FIGCAPTION;
	else if(strtag == "GUMBO_TAG_MAIN")
	    tag = GUMBO_TAG_MAIN;
	else if(strtag == "GUMBO_TAG_DIV")
	    tag = GUMBO_TAG_DIV;
	else if(strtag == "GUMBO_TAG_A")
	    tag = GUMBO_TAG_A;
	else if(strtag == "GUMBO_TAG_EM")
	    tag = GUMBO_TAG_EM;
	else if(strtag == "GUMBO_TAG_STRONG")
	    tag = GUMBO_TAG_STRONG;
	else if(strtag == "GUMBO_TAG_SMALL")
	    tag = GUMBO_TAG_SMALL;
	else if(strtag == "GUMBO_TAG_S")
	    tag = GUMBO_TAG_S;
	else if(strtag == "GUMBO_TAG_CITE")
	    tag = GUMBO_TAG_CITE;
	else if(strtag == "GUMBO_TAG_Q")
	    tag = GUMBO_TAG_Q;
	else if(strtag == "GUMBO_TAG_DFN")
	    tag = GUMBO_TAG_DFN;
	else if(strtag == "GUMBO_TAG_ABBR")
	    tag = GUMBO_TAG_ABBR;
	else if(strtag == "GUMBO_TAG_DATA")
	    tag = GUMBO_TAG_DATA;
	else if(strtag == "GUMBO_TAG_TIME")
	    tag = GUMBO_TAG_TIME;
	else if(strtag == "GUMBO_TAG_CODE")
	    tag = GUMBO_TAG_CODE;
	else if(strtag == "GUMBO_TAG_VAR")
	    tag = GUMBO_TAG_VAR;
	else if(strtag == "GUMBO_TAG_SAMP")
	    tag = GUMBO_TAG_SAMP;
	else if(strtag == "GUMBO_TAG_KBD")
	    tag = GUMBO_TAG_KBD;
	else if(strtag == "GUMBO_TAG_SUB")
	    tag = GUMBO_TAG_SUB;
	else if(strtag == "GUMBO_TAG_SUP")
	    tag = GUMBO_TAG_SUP;
	else if(strtag == "GUMBO_TAG_I")
	    tag = GUMBO_TAG_I;
	else if(strtag == "GUMBO_TAG_B")
	    tag = GUMBO_TAG_B;
	else if(strtag == "GUMBO_TAG_U")
	    tag = GUMBO_TAG_U;
	else if(strtag == "GUMBO_TAG_MARK")
	    tag = GUMBO_TAG_MARK;
	else if(strtag == "GUMBO_TAG_RUBY")
	    tag = GUMBO_TAG_RUBY;
	else if(strtag == "GUMBO_TAG_RT")
	    tag = GUMBO_TAG_RT;
	else if(strtag == "GUMBO_TAG_RP")
	    tag = GUMBO_TAG_RP;
	else if(strtag == "GUMBO_TAG_BDI")
	    tag = GUMBO_TAG_BDI;
	else if(strtag == "GUMBO_TAG_BDO")
	    tag = GUMBO_TAG_BDO;
	else if(strtag == "GUMBO_TAG_SPAN")
	    tag = GUMBO_TAG_SPAN;
	else if(strtag == "GUMBO_TAG_BR")
	    tag = GUMBO_TAG_BR;
	else if(strtag == "GUMBO_TAG_WBR")
	    tag = GUMBO_TAG_WBR;
	else if(strtag == "GUMBO_TAG_INS")
	    tag = GUMBO_TAG_INS;
	else if(strtag == "GUMBO_TAG_DEL")
	    tag = GUMBO_TAG_DEL;
	else if(strtag == "GUMBO_TAG_IMAGE")
	    tag = GUMBO_TAG_IMAGE;
	else if(strtag == "GUMBO_TAG_IMG")
	    tag = GUMBO_TAG_IMG;
	else if(strtag == "GUMBO_TAG_IFRAME")
	    tag = GUMBO_TAG_IFRAME;
	else if(strtag == "GUMBO_TAG_EMBED")
	    tag = GUMBO_TAG_EMBED;
	else if(strtag == "GUMBO_TAG_OBJECT")
	    tag = GUMBO_TAG_OBJECT;
	else if(strtag == "GUMBO_TAG_PARAM")
	    tag = GUMBO_TAG_PARAM;
	else if(strtag == "GUMBO_TAG_VIDEO")
	    tag = GUMBO_TAG_VIDEO;
	else if(strtag == "GUMBO_TAG_AUDIO")
	    tag = GUMBO_TAG_AUDIO;
	else if(strtag == "GUMBO_TAG_SOURCE")
	    tag = GUMBO_TAG_SOURCE;
	else if(strtag == "GUMBO_TAG_TRACK")
	    tag = GUMBO_TAG_TRACK;
	else if(strtag == "GUMBO_TAG_CANVAS")
	    tag = GUMBO_TAG_CANVAS;
	else if(strtag == "GUMBO_TAG_MAP")
	    tag = GUMBO_TAG_MAP;
	else if(strtag == "GUMBO_TAG_AREA")
	    tag = GUMBO_TAG_AREA;
	else if(strtag == "GUMBO_TAG_MATH")
	    tag = GUMBO_TAG_MATH;
	else if(strtag == "GUMBO_TAG_MI")
	    tag = GUMBO_TAG_MI;
	else if(strtag == "GUMBO_TAG_MO")
	    tag = GUMBO_TAG_MO;
	else if(strtag == "GUMBO_TAG_MN")
	    tag = GUMBO_TAG_MN;
	else if(strtag == "GUMBO_TAG_MS")
	    tag = GUMBO_TAG_MS;
	else if(strtag == "GUMBO_TAG_MTEXT")
	    tag = GUMBO_TAG_MTEXT;
	else if(strtag == "GUMBO_TAG_MGLYPH")
	    tag = GUMBO_TAG_MGLYPH;
	else if(strtag == "GUMBO_TAG_MALIGNMARK")
	    tag = GUMBO_TAG_MALIGNMARK;
	else if(strtag == "GUMBO_TAG_ANNOTATION_XML")
	    tag = GUMBO_TAG_ANNOTATION_XML;
	else if(strtag == "GUMBO_TAG_SVG")
	    tag = GUMBO_TAG_SVG;
	else if(strtag == "GUMBO_TAG_FOREIGNOBJECT")
	    tag = GUMBO_TAG_FOREIGNOBJECT;
	else if(strtag == "GUMBO_TAG_DESC")
	    tag = GUMBO_TAG_DESC;
	else if(strtag == "GUMBO_TAG_TABLE")
	    tag = GUMBO_TAG_TABLE;
	else if(strtag == "GUMBO_TAG_CAPTION")
	    tag = GUMBO_TAG_CAPTION;
	else if(strtag == "GUMBO_TAG_COLGROUP")
	    tag = GUMBO_TAG_COLGROUP;
	else if(strtag == "GUMBO_TAG_COL")
	    tag = GUMBO_TAG_COL;
	else if(strtag == "GUMBO_TAG_TBODY")
	    tag = GUMBO_TAG_TBODY;
	else if(strtag == "GUMBO_TAG_THEAD")
	    tag = GUMBO_TAG_THEAD;
	else if(strtag == "GUMBO_TAG_TFOOT")
	    tag = GUMBO_TAG_TFOOT;
	else if(strtag == "GUMBO_TAG_TR")
	    tag = GUMBO_TAG_TR;
	else if(strtag == "GUMBO_TAG_TD")
	    tag = GUMBO_TAG_TD;
	else if(strtag == "GUMBO_TAG_TH")
	    tag = GUMBO_TAG_TH;
	else if(strtag == "GUMBO_TAG_FORM")
	    tag = GUMBO_TAG_FORM;
	else if(strtag == "GUMBO_TAG_FIELDSET")
	    tag = GUMBO_TAG_FIELDSET;
	else if(strtag == "GUMBO_TAG_LEGEND")
	    tag = GUMBO_TAG_LEGEND;
	else if(strtag == "GUMBO_TAG_LABEL")
	    tag = GUMBO_TAG_LABEL;
	else if(strtag == "GUMBO_TAG_INPUT")
	    tag = GUMBO_TAG_INPUT;
	else if(strtag == "GUMBO_TAG_BUTTON")
	    tag = GUMBO_TAG_BUTTON;
	else if(strtag == "GUMBO_TAG_SELECT")
	    tag = GUMBO_TAG_SELECT;
	else if(strtag == "GUMBO_TAG_DATALIST")
	    tag = GUMBO_TAG_DATALIST;
	else if(strtag == "GUMBO_TAG_OPTGROUP")
	    tag = GUMBO_TAG_OPTGROUP;
	else if(strtag == "GUMBO_TAG_OPTION")
	    tag = GUMBO_TAG_OPTION;
	else if(strtag == "GUMBO_TAG_TEXTAREA")
	    tag = GUMBO_TAG_TEXTAREA;
	else if(strtag == "GUMBO_TAG_KEYGEN")
	    tag = GUMBO_TAG_KEYGEN;
	else if(strtag == "GUMBO_TAG_OUTPUT")
	    tag = GUMBO_TAG_OUTPUT;
	else if(strtag == "GUMBO_TAG_PROGRESS")
	    tag = GUMBO_TAG_PROGRESS;
	else if(strtag == "GUMBO_TAG_METER")
	    tag = GUMBO_TAG_METER;
	else if(strtag == "GUMBO_TAG_DETAILS")
	    tag = GUMBO_TAG_DETAILS;
	else if(strtag == "GUMBO_TAG_SUMMARY")
	    tag = GUMBO_TAG_SUMMARY;
	else if(strtag == "GUMBO_TAG_MENU")
	    tag = GUMBO_TAG_MENU;
	else if(strtag == "GUMBO_TAG_MENUITEM")
	    tag = GUMBO_TAG_MENUITEM;
	else if(strtag == "GUMBO_TAG_APPLET")
	    tag = GUMBO_TAG_APPLET;
	else if(strtag == "GUMBO_TAG_ACRONYM")
	    tag = GUMBO_TAG_ACRONYM;
	else if(strtag == "GUMBO_TAG_BGSOUND")
	    tag = GUMBO_TAG_BGSOUND;
	else if(strtag == "GUMBO_TAG_DIR")
	    tag = GUMBO_TAG_DIR;
	else if(strtag == "GUMBO_TAG_FRAME")
	    tag = GUMBO_TAG_FRAME;
	else if(strtag == "GUMBO_TAG_FRAMESET")
	    tag = GUMBO_TAG_FRAMESET;
	else if(strtag == "GUMBO_TAG_NOFRAMES")
	    tag = GUMBO_TAG_NOFRAMES;
	else if(strtag == "GUMBO_TAG_ISINDEX")
	    tag = GUMBO_TAG_ISINDEX;
	else if(strtag == "GUMBO_TAG_LISTING")
	    tag = GUMBO_TAG_LISTING;
	else if(strtag == "GUMBO_TAG_XMP")
	    tag = GUMBO_TAG_XMP;
	else if(strtag == "GUMBO_TAG_NEXTID")
	    tag = GUMBO_TAG_NEXTID;
	else if(strtag == "GUMBO_TAG_NOEMBED")
	    tag = GUMBO_TAG_NOEMBED;
	else if(strtag == "GUMBO_TAG_PLAINTEXT")
	    tag = GUMBO_TAG_PLAINTEXT;
	else if(strtag == "GUMBO_TAG_RB")
	    tag = GUMBO_TAG_RB;
	else if(strtag == "GUMBO_TAG_STRIKE")
	    tag = GUMBO_TAG_STRIKE;
	else if(strtag == "GUMBO_TAG_BASEFONT")
	    tag = GUMBO_TAG_BASEFONT;
	else if(strtag == "GUMBO_TAG_BIG")
	    tag = GUMBO_TAG_BIG;
	else if(strtag == "GUMBO_TAG_BLINK")
	    tag = GUMBO_TAG_BLINK;
	else if(strtag == "GUMBO_TAG_CENTER")
	    tag = GUMBO_TAG_CENTER;
	else if(strtag == "GUMBO_TAG_FONT")
	    tag = GUMBO_TAG_FONT;
	else if(strtag == "GUMBO_TAG_MARQUEE")
	    tag = GUMBO_TAG_MARQUEE;
	else if(strtag == "GUMBO_TAG_MULTICOL")
	    tag = GUMBO_TAG_MULTICOL;
	else if(strtag == "GUMBO_TAG_NOBR")
	    tag = GUMBO_TAG_NOBR;
	else if(strtag == "GUMBO_TAG_SPACER")
	    tag = GUMBO_TAG_SPACER;
	else if(strtag == "GUMBO_TAG_TT")
	    tag = GUMBO_TAG_TT;
	else if(strtag == "GUMBO_TAG_RTC")
	    tag = GUMBO_TAG_RTC;
	return tag;
}

void CgumboServer::ReplaceStr(string &strContent,const string &strSrc,const string &strDest,bool ignoreCase)
{
	string strCopy(strContent);
	string strSrcCopy(strSrc);

	string::size_type pos = 0;
	string::size_type srclen = strSrc.size();
	string::size_type dstlen = strDest.size();
	//忽略大小写时，先都转换成小写，然后定位位置，再对源字符串进行替换
	if(ignoreCase)
	{
		//源字符串转化成小写
		std::transform(strCopy.begin(),strCopy.end(),strCopy.begin(),(int (*)(int))tolower);
		std::transform(strSrcCopy.begin(),strSrcCopy.end(),strSrcCopy.begin(),(int (*)(int))tolower);
	}

	while( (pos=strCopy.find(strSrcCopy, pos)) != string::npos)
	{
		strContent.replace(pos, srclen, strDest);
		strCopy.replace(pos, srclen, strDest);
		pos += dstlen;
	}
}

