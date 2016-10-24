package information.information;

import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field.Store;
import org.apache.lucene.document.StringField;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version; 

public class test {
	public void createIndex() throws Exception {

        // 模拟一条文章数据
        Article a = new Article();
        a.setId(1);
        a.setTitle("全文检索");
        a.setContent("我们主要是做站内搜索（或叫系统内搜索），即对系统内的资源进行搜索");

        // 建立索引
        Directory dir = FSDirectory.open(Paths.get("./indexDir/"));
        IndexWriterConfig indexWriterConfig = new IndexWriterConfig(new StandardAnalyzer());
        IndexWriter indexWriter = new IndexWriter(dir, indexWriterConfig);

        Document doc = new Document();
        doc.add(new StringField("id", a.getId().toString(), Store.YES));
        doc.add(new TextField("title", a.getTitle(), Store.YES));
        doc.add(new TextField("content", a.getContent(), Store.YES));

        indexWriter.addDocument(doc);
        indexWriter.close();
    }
	
	 public void search() throws Exception {

	        String queryString = "资源";
	        Analyzer analyzer = new StandardAnalyzer();
	        analyzer.setVersion(Version.LUCENE_6_1_0);
	        QueryParser queryParser = new QueryParser("content", analyzer);
	        Query query = queryParser.parse(queryString);
	        // IndexReader indexReader =
	        // DirectoryReader.open(FSDirectory.open(Paths.get("./indexDir/")));
	        DirectoryReader directoryReader = DirectoryReader.open(FSDirectory.open(Paths.get("./indexDir/")));
	        IndexReader indexReader = directoryReader;
	        IndexSearcher indexSearcher = new IndexSearcher(indexReader);
	        TopDocs topDocs = indexSearcher.search(query, 10);
	        ScoreDoc[] scoreDocs = topDocs.scoreDocs;

	        List<Article> articles = new ArrayList<Article>();
	        for (int i = 0; i < scoreDocs.length; i++) {
	            ScoreDoc scoreDoc = scoreDocs[i];
	            Document doc = indexSearcher.doc(scoreDoc.doc);
	            Article a = new Article();
	            a.setId(Integer.parseInt(doc.get("id")));
	            a.setTitle(doc.get("title"));
	            a.setContent(doc.get("content"));
	            System.out.println(a.toString());
	            articles.add(a);
	        }
	        // 显示结果
	        System.out.println("总的记录数为： " + topDocs.totalHits);
	        System.out.println(articles.toString());
	        for (Article a : articles) {
	            System.out.println("-----------搜索结果如下-----------------");
	            System.out.println(">>>id: " + a.getId());
	            System.out.println(">>>title:" + a.getTitle());
	            System.out.println(">>>content:" + a.getContent());
	        }
	        indexReader.close();
	        analyzer.close();

	    }
	 
	 public static void main(String[] args) throws Exception {
		 test a = new test();
		 a.createIndex();
		 a.search();
	 }
}
