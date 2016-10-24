package information.information;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
 
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter; 
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs; 

public class LuceneDemo {
	public static List<File> getFileList(String strPath) {
		List<File> filelist = new ArrayList<File>();
		File dir = new File(strPath);
		File[] files = dir.listFiles();
		if (files != null) {
			for (int i = 0; i < files.length; i++) {
				if (files[i].isDirectory()) {
					getFileList(files[i].getAbsolutePath());
				} else { 
					filelist.add(files[i]);
				}
			}

		}
		return filelist;
	}

	public static String readFile(InputStream file) throws IOException {
	//	String content = "";
		 InputStreamReader isr = new InputStreamReader(file, "GBK");   
		  BufferedReader br = new BufferedReader(isr);   
		  String line = null;   	
		  StringBuilder sb = new StringBuilder();
		  while ((line = br.readLine()) != null) {   
			  line += line;   
			  line += "\r\n"; // 补上换行符   
			  sb.append(line);
		  }   
	/*	BufferedReader bf = new BufferedReader(new FileReader(file));
		StringBuilder sb = new StringBuilder();
		while (content != null) {
			content = bf.readLine();
			if (content == null) {
				break;
			}
			sb.append(content.trim()+"\r\n");
		}
		bf.close();
*/
		return sb.toString();
	}
 
	public static void main(String[] args) throws IOException, ParseException, java.text.ParseException {
		// TODO Auto-generated method stub
		System.out.println("Lucene demo is begin.........");//new StandardAnalyzer();//new StandardAnalyzer();
		IndexWriter indexWriter = LuceneUtils.getIndexWriter();

		indexWriter.deleteAll();
		List<File> filelist = getFileList("E:/test");
		int id = 0;
		for (File file : filelist) { 
			String context = readFile(new FileInputStream(file)); 
			Article article = new Article();
			id++;
			article.setId(id);
			article.setAuthor("zhangjie");
			article.setContent(context);
			article.setCreateDt(new Timestamp(file.lastModified()));
			article.setTitle(file.getName());
			article.setUrl(file.getAbsolutePath()); 
			Document doc = ArticleDocumentUtils.article2Document(article);
			indexWriter.addDocument(doc);
		}
		indexWriter.close();
		
		IndexSearcher indexSearcher = LuceneUtils.getIndexSearcher();
		 Scanner input = new Scanner(System.in);
		System.out.println("Enter seach string: "); 
		String queryString =  input.next();
		while(queryString != null ){
			QueryParser queryParser = new QueryParser("content", LuceneUtils.getAnalyzer());
	        Query query = queryParser.parse(queryString);
	        TopDocs topDocs = indexSearcher.search(query, 1000);
	        ScoreDoc[] scoreDocs = topDocs.scoreDocs;

	        List<Article> articles = new ArrayList<Article>();
	        for (int i = 0; i < scoreDocs.length; i++) {
	            ScoreDoc scoreDoc = scoreDocs[i];
	            Document doc = indexSearcher.doc(scoreDoc.doc);
	            if(doc == null)
	            	continue;
	            
	            Article a = new Article();
	            a.setId(Integer.parseInt(doc.get("id")));
	            a.setTitle(doc.get("title"));
	            a.setContent(doc.get("content"));
	            a.setAuthor(doc.get("author"));
	            a.setUrl(doc.get("url"));
	            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	            Date date = sdf.parse(doc.get("createDt"));
	            a.setCreateDt(date);
	            System.out.println(a.toString());
	            articles.add(a);
	        }
	        
			System.out.println("Enter seach string: "); 
			queryString =  input.next();
		}
        
        
        System.out.println("Lucene demo is end.........");
	}

}
