import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;

public class AddWeight extends HttpServlet{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public void addWeight(HttpServletRequest request) throws Exception{
		String start = request.getParameter("node1");
		String end = request.getParameter("node2");
		int start_int = Integer.parseInt(start);
		int end_int = Integer.parseInt(end);
		
		File file = new File("storedata.txt");
        FileReader in = new FileReader(file);
        BufferedReader ini = new BufferedReader(in);
        int edge[][]=new int[][]{{1,5},{3,5},{2,3},{2,4},{4,6},{6,7},{6,8},{7,8},{8,9},{8,10}};
        double[][] distance = new double[10][10];
        ini.close();
        
        for (int i = 0; i < edge.length; i++) {
            distance[edge[i][0] - 1][edge[i][1] - 1] = Double.parseDouble(ini.readLine());
        }
        distance[start_int-1][end_int-1]--;
        
        FileWriter fw = new FileWriter(file);
        for(int i = 0; i < edge.length;i++){
        	fw.write((distance[edge[i][0] - 1][edge[i][1] - 1]+1) + "\r\n");
        }
        fw.close();
    }
}