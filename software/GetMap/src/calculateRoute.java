import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;

public class calculateRoute extends HttpServlet{
    public String calculate(HttpServletRequest request) throws Exception{
		String start = request.getParameter("begin");
		String end = request.getParameter("end");
		int start_int = Integer.parseInt(start);
		int end_int = Integer.parseInt(end);
		
		int result[] = shortestPath(start_int, end_int);
		String output = "Best path is ";
		for(int i = 0; i < result.length-1 && result[i] != -1; i++){
			output += (result[i] + " -> ");
		}
		output += result[result.length-1];
		return output;
	}
    
	public int[] shortestPath(int start, int end) throws Exception{
		final int MAX = 100;
		int vNum=10;
	    int edgeNum=11;
	    int edge[][]=new int[][]{{1,5},{3,5},{2,3},{2,4},{4,6},{6,7},{6,8},{7,8},{8,9},{8,10}};

        //二维数值用来表示图
        double distance[][] = new double[vNum][vNum];
        int[][] path = new int[vNum][vNum];

        //进行初始化，任意两个点的距离无限大
        for (int i = 0; i < vNum; i++) {
            for (int j = 0; j < vNum; j++) {
                distance[i][j] = MAX;
                if (i == j)
                    distance[i][j] = 0;
            }
        }
        //读取数据，设置权值
        File file = new File("storedata.txt");
        FileReader in = new FileReader(file);
        BufferedReader ini = new BufferedReader(in);
        
        for (int i = 0; i < edge.length; i++) {
            distance[edge[i][0] - 1][edge[i][1] - 1] = Double.parseDouble(ini.readLine());
        }
        ini.close();
        
        for (int i = 0; i < vNum; i++) {
            for (int j = 0; j < vNum; j++) {
                int index = i;
                for (int k = 0; k < vNum; k++) {
                    if (distance[i][j] > distance[i][k] + distance[k][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        index = k;
                    }
                }
                path[i][j] = index;
            }

        }

        int[] result = new int[vNum];
        for (int i = 0; i < vNum; i++) {
            result[i] = -1;
        }
        int tmp = 0;
        result[tmp] = end + 1;
        tmp = tmp + 1;
        while (true) {
            if (end == start)
                break;
            result[tmp] = path[start][end] + 1;
            tmp = tmp + 1;
            end = path[start][end];

        }
        return result;
    }
}
