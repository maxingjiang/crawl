package information.information;
import java.io.IOException;
import java.nio.file.Paths;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.index.IndexWriterConfig.OpenMode;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;
 
/**
 *  
 *
 */
public class LuceneUtils {

    private static Directory dir;

    public static Directory getDir() {
        return dir;
    }

    public static Analyzer getAnalyzer() {
        return analyzer;
    }

    private static Analyzer analyzer;

    /**
     * 获得一个用于操作索引库的IndexWriter对象
     * 
     * @return
     */
    public static IndexWriter getIndexWriter() {
        try {
            Directory dir = FSDirectory.open(Paths.get("E:/indexDir/")); 
            analyzer = new StandardAnalyzer();
            analyzer.setVersion(Version.LUCENE_6_1_0);
            IndexWriterConfig indexWriterConfig = new IndexWriterConfig(analyzer);
            indexWriterConfig.setOpenMode(OpenMode.CREATE_OR_APPEND);  
            IndexWriter indexWriter = new IndexWriter(dir, indexWriterConfig);
            return indexWriter != null ? indexWriter : null;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 获得一个索引库查询对象
     * 
     * @return
     */
    public static IndexSearcher getIndexSearcher() {

        try {
            DirectoryReader directoryReader = DirectoryReader.open(FSDirectory.open(Paths.get("E:/indexDir/")));
            IndexReader indexReader = directoryReader;
            IndexSearcher indexSearcher = new IndexSearcher(indexReader);
            return indexSearcher != null ? indexSearcher : null;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 释放IndexWriter资源
     * 
     * @param indexWriter
     */
    public static void closeIndexWriter(IndexWriter indexWriter) {
        try {
            if (indexWriter != null) {
                indexWriter.close();
                indexWriter = null;
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    /**
     * 释放IndexSearcher资源
     * 
     * @param indexSearcher
     */
    public static void closeIndexSearcher(IndexSearcher indexSearcher) {
        try {
            if (indexSearcher != null) {
                indexSearcher = null;
            }
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}