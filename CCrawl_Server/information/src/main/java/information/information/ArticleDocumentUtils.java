package information.information;

import java.text.ParseException;
import java.util.Date;

import org.apache.lucene.document.DateTools;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.Field.Store;
import org.apache.lucene.document.StringField;
import org.apache.lucene.document.TextField; 

/**
 * @author 
 *
 */
public class ArticleDocumentUtils {

    /**
     * Article转换成Licene的Document
     * 
     * @param article
     * @return
     */
    public static Document article2Document(Article article) {
        Document doc = new Document();
        doc.add(new StringField("id", article.getId().toString(), Store.YES));
        doc.add(new TextField("title", article.getTitle(), Store.YES));
        doc.add(new TextField("url", article.getUrl(), Store.YES));
        doc.add(new TextField("author", article.getAuthor(), Store.YES));
        doc.add(new TextField("createDt", article.getCreateDt().toLocaleString(),  Store.YES));
        doc.add(new TextField("content", article.getContent(), Store.YES));
        return doc != null ? doc : null;
    }

    /**
     * 将Document转换回Article
     * 
     * @param document
     * @return
     * @throws ParseException 
     */
    public static Article document2Article(Document document) throws ParseException {
        Article a = new Article();
        a.setId(Integer.parseInt(document.get("id")));
        a.setTitle(document.get("title"));
        a.setContent(document.get("content"));
        a.setUrl(document.get("url"));
        a.setAuthor(document.get("author"));
        a.setCreateDt( DateTools.stringToDate(document.get("createDt")));
        return a != null ? a : null;
    }

}