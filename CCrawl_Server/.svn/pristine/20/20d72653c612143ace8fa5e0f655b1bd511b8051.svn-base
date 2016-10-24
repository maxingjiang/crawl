package information.information;

import java.io.IOException;
import java.util.ArrayList; 
import java.util.List;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryparser.classic.MultiFieldQueryParser;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.util.Version;
 
 
public class ArticleIndexDao {
    /**
     * 将新的数据保存到索引库
     * 
     * @param article
     */
    public void save(Article article) {
        IndexWriter indexWriter = null;
        try {
            // 1. article --> document
            Document doc = ArticleDocumentUtils.article2Document(article);
            // 2. indexWriter.addDocument(document)
            indexWriter = LuceneUtils.getIndexWriter();
            indexWriter.addDocument(doc);
            // 临时代码
            indexWriter.close();
        } catch (IOException e) {
            throw new RuntimeException("ArticleIndexDao--save方法出错！\n" + e);
        } finally {
            LuceneUtils.closeIndexWriter(indexWriter);
        }
    }

    /**
     * 删除索引
     * 
     * @param id
     */
    public void delete(Integer id) {
        IndexWriter indexWriter = null;
        try {
            indexWriter = LuceneUtils.getIndexWriter();
            indexWriter.deleteDocuments(new Term("id", id.toString()));
        } catch (IOException e) {
            throw new RuntimeException("ArticleIndexDao--save方法出错！\n" + e);
        } finally {
            LuceneUtils.closeIndexWriter(indexWriter);
        }
    }

    /**
     * 更新索引 <br>
     * 更新操作代价很高，一般采取先删除对应的索引，然后在创建这个索引的方式
     * 
     * @param article
     */
    public void update(Article article) {
        IndexWriter indexWriter = null;
        try {
            Term term = new Term("id", article.getId().toString());
            indexWriter = LuceneUtils.getIndexWriter();
            indexWriter.deleteDocuments(term);
            Document doc = ArticleDocumentUtils.article2Document(article);
            indexWriter.addDocument(doc);
        } catch (IOException e) {
            throw new RuntimeException("ArticleIndexDao--save方法出错！\n" + e);
        } finally {
            LuceneUtils.closeIndexWriter(indexWriter);
        }
    }

    /**
     * 从索引库中查询
     * 
     * @param queryString
     *            查询字符串
     * @return
     */
    public List<Article> search(String queryString) {
        try {
            // 1.queryString -->>Query 
            
            String[] queryFields = new String[] { "title", "url", "author", "createDt", "content" };
            Analyzer analyzer = new StandardAnalyzer();
           
            analyzer.setVersion(Version.LUCENE_6_0_0.LUCENE_6_1_0);
            QueryParser queryParser = new MultiFieldQueryParser(queryFields, analyzer);
            Query query = queryParser.parse(queryString);
            // 2. 查询，得到topDocs
            IndexSearcher indexSearcher = LuceneUtils.getIndexSearcher();
            TopDocs topDocs = indexSearcher.search(query, 1000);
            // 3.处理结果并返回
            int totalHits = topDocs.totalHits;
            ScoreDoc[] scoreDocs = topDocs.scoreDocs;
            List<Article> articles = new ArrayList<Article>();
            for (int i = 0; i < scoreDocs.length; i++) {
                ScoreDoc scoreDoc = scoreDocs[i];
                Document doc = indexSearcher.doc(scoreDoc.doc);
                Article a = ArticleDocumentUtils.document2Article(doc);
                articles.add(a);
            }
            LuceneUtils.closeIndexSearcher(indexSearcher);
            return articles.size() > 0 ? articles : null;
        } catch (Exception e) {
            throw new RuntimeException("ArticleIndexDao-->> search方法出错！\n" + e);
        }
    }


}