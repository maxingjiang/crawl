/*
 * CHtmlNode.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: root
 */

#include "CHtmlNode.h"
#include "gumbo/util.h"
#include "callpy.h"

HtmlNode::HtmlNode()
{
	m_parent = NULL;
	m_child.clear();
	m_tag.clear();
	m_attributes.clear();
	m_value.clear();
}
HtmlNode::~HtmlNode()
{

}

CHtmlNode::CHtmlNode()
{
    m_node = new HtmlNode();
}

CHtmlNode::~CHtmlNode()
{
	deleteHtmlNode(m_node);
}

//parse
int CHtmlNode::getNodeData(const string &body)
{
	GumboOutput *output;
	output=gumbo_parse(body.c_str());
	if(!output)
	{
        return 1;
    }
    /* 获取我们想要的内容 <dt>*/
	getdata(m_node, output->root);
    /* 释放资源 */
    gumbo_destroy_output(&kGumboDefaultOptions,output);
	return 0;
}


/**********************************************************************************
 *功能：将DOM节点内部所有文本内容按顺序连接，组成原始网页显示的文本childNodeText.
 * m_child与m_value的值要互相穿插连接，当m_child与m_value的其中某一个被连接完了，则将另一个的
 * 所有剩余元素按vector顺序连接在childNodeText后面。
 * 函数使用递归的方式将当前节点的子节点的Text取出来。
 **********************************************************************************/
string HtmlNode::getNodeText()
{
    string childNodeText;

    if(m_tag == "script")
        return "";

    unsigned int minSize = m_child.size() < m_value.size() ? m_child.size() : m_value.size();
    unsigned int maxSize = m_child.size() > m_value.size() ? m_child.size() : m_value.size();

    for(unsigned int i = 0; i < maxSize; i++)
    {
        if(m_child.size() < m_value.size())
        {
            if(minSize > i)//m_child与m_value都没被取完
            {
                childNodeText = childNodeText + m_value[i] + ((HtmlNode*)(m_child[i]))->getNodeText();
            }
            else//m_child被取完了，只剩m_value
            {
                childNodeText = childNodeText + m_value[i];
            }
        }
        else
        {
            if(minSize > i)//m_child与m_value都没被取完
            {
                childNodeText = childNodeText + m_value[i] + ((HtmlNode*)(m_child[i]))->getNodeText();
            }
            else//m_value被取完了，只剩m_child
            {
                childNodeText = childNodeText + ((HtmlNode*)(m_child[i]))->getNodeText();
            }
        }
    }

    return childNodeText;
}

void CHtmlNode::printfNodeList()
{
    if(!m_node)
    {
        cout << "NodeList is empty!" << endl;
        return ;
    }

    printfNode(m_node);
}
void CHtmlNode::printfMapAttr(map<string,string> &attr)
{
    map<string,string>::iterator attr_it;
    for (attr_it = attr.begin(); attr_it != attr.end(); attr_it++)
    {
        cout << attr_it->first << " = " << attr_it->second << " ";
    }
}

void CHtmlNode::printfNode(HtmlNode *htmlNode)
{
    cout<< htmlNode->m_tag << " => value: " << htmlNode->getNodeText() << endl;
    return;
}

//Gumbo to HtmlNode
void CHtmlNode::getdata(HtmlNode *phtmlnode, GumboNode *gnode)
{
	GumboVector *children = NULL;
	GumboAttribute *attr = NULL;

    if(gnode->type != GUMBO_NODE_ELEMENT)
        return ;

    children = &gnode->v.element.children;
	if(gnode->v.element.tag >= GUMBO_TAG_HTML && gnode->v.element.tag <= GUMBO_TAG_RTC)
	{
		phtmlnode->m_tag = getTag(gnode->v.element.tag);
		GumboVector *attributes = &gnode->v.element.attributes;
		if(attributes != NULL)
		{
            /*把当前节点的所有属性放入map中*/
			for (unsigned int j = 0; j < attributes->length; ++j)
			{
				GumboAttribute* attr2 = (GumboAttribute*)attributes->data[j];

                phtmlnode->m_attributes.insert(pair<string,string>(attr2->name,attr2->value));
			}
		}
        /*把当前节点的所有文本内容放入vector中*/
        for (unsigned int i = 0; i < children->length; i++)
        {
            if(children != NULL && (GumboNode *)children->data[i] != NULL)
			{
                insertNodeData(phtmlnode, (GumboNode *)children->data[i], attr);
            }
		}
    }

	/* 查找所有标签 */
	for(unsigned i = 0; i < children->length; ++i)
	{
        //过滤GumboNode中的非元素节点
        if(((GumboNode*)children->data[i])->type != GUMBO_NODE_ELEMENT)
            continue ;

		HtmlNode *node = new HtmlNode();
		phtmlnode->m_child.push_back(node);
		node->m_parent = phtmlnode;
		getdata(node, (GumboNode*)children->data[i]);
	}
}

void CHtmlNode::insertNodeData(HtmlNode *phtmlnode, GumboNode *gnode, GumboAttribute *attr)
{
    string src = "";

	if(gnode->type == GUMBO_NODE_TEXT)
	{
        if(gnode->v.element.children.length == 0) //当无子节点时，文本内容赋值为空
		{
            src = "";
		}
		else
        {
            string value = gnode->v.text.text;
            src = value;
		}
	}
    //把文本push到vector中，且过滤非元素的节点内容
    if(gnode->type != GUMBO_NODE_ELEMENT)
    {
        phtmlnode->m_value.push_back(src);
    }
}

void CHtmlNode::deleteHtmlNode(HtmlNode *node)
{
	if(node != NULL)
	{
		for(unsigned int i = 0; i < node->m_child.size(); ++i)
		{
            node->m_attributes.clear();
			deleteHtmlNode(node->m_child[i]);
		}
		delete node;
	}
}

string CHtmlNode::getTag(GumboTag tag)
{
	 string strtag[] = {
			 "html",
			 "head",
			 "title",
			 "base",
			 "link",
			 "meta",
			 "style",
			 "script",
			 "noscript",
			 "template",
			 "body",
			 "article",
			 "section",
			 "nav",
			 "aside",
			 "h1",
			 "h2",
			 "h3",
			 "h4",
			 "h5",
			 "h6",
			 "hgroup",
			 "header",
			 "footer",
			 "address",
			 "p",
			 "hr",
			 "pre",
			 "blockquote",
			 "ol",
			 "ul",
			 "li",
			 "dl",
			 "dt",
			 "dd",
			 "figure",
			 "figcaption",
			 "main",
			 "div",
			 "a",
			 "em",
			 "strong",
			 "small",
			 "s",
			 "cite",
			 "q",
			 "dfn",
			 "abbr",
			 "data",
			 "time",
			 "code",
			 "var",
			 "samp",
			 "kbd",
			 "sub",
			 "sup",
			 "i",
			 "b",
			 "u",
			 "mark",
			 "ruby",
			 "rt",
			 "rp",
			 "bdi",
			 "bdo",
			 "span",
			 "br",
			 "wbr",
			 "ins",
			 "del",
			 "image",
			 "img",
			 "iframe",
			 "embed",
			 "object",
			 "param",
			 "video",
			 "audio",
			 "source",
			 "track",
			 "canvas",
			 "map",
			 "area",
			 "math",
			 "mi",
			 "mo",
			 "mn",
			 "ms",
			 "mtext",
			 "mglyph",
			 "malignmark",
			 "annotation_xml",
			 "svg",
			 "foreignobject",
			 "desc",
			 "table",
			 "caption",
			 "colgroup",
			 "col",
			 "tbody",
			 "thead",
			 "tfoot",
			 "tr",
			 "td",
			 "th",
			 "form",
			 "fieldset",
			 "legend",
			 "label",
			 "input",
			 "button",
			 "select",
			 "datalist",
			 "optgroup",
			 "option",
			 "textarea",
			 "keygen",
			 "output",
			 "progress",
			 "meter",
			 "details",
			 "summary",
			 "menu",
			 "menuitem",
			 "applet",
			 "acronym",
			 "bgsound",
			 "dir",
			 "frame",
			 "frameset",
			 "noframes",
			 "isindex",
			 "listing",
			 "xmp",
			 "nextid",
			 "noembed",
			 "plaintext",
			 "rb",
			 "strike",
			 "basefont",
			 "big",
			 "blink",
			 "center",
			 "font",
			 "marquee",
			 "multicol",
			 "nobr",
			 "spacer",
			 "tt",
			 "rtc"
	 };
	 if(tag >= GUMBO_TAG_HTML && tag <= GUMBO_TAG_RTC)
	 {
		 return strtag[tag];
	 }
	 else
	 {
		 return "";
	 }
}

