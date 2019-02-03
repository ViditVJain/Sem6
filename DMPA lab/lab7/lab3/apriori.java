import java.util.*;
import java.io.*;

public class apriori {
	static int dat[][] = new int[100][4];

	public static int readData(){
		int n = 0;
		try{
			BufferedReader br = new BufferedReader(new FileReader("thing.csv"));
			String line = "";
			String temp[];
			
			line = br.readLine();
			while ((line = br.readLine()) != null){
				temp = line.split(",");
				// System.out.println();
				dat[n][0] = Integer.parseInt(temp[0]);
				dat[n][1] = Integer.parseInt(temp[1]);
				dat[n][2] = Integer.parseInt(temp[2]);
				dat[n][3] = Integer.parseInt(temp[3]);
				System.out.println(dat[n][0]+" "+dat[n][1]+" "+dat[n][2]+" "+dat[n][3]);
				n++;
			}
		}
		catch (Exception e){
			System.out.println(e);
		}
		return n;
	}

	public static void main(String[] args) {
		int n = readData();
		
		System.out.println();
		int c1[] = new int[4];
		for (int i=0; i<4; i++) {
			int ct = 0;
			for (int j=0; j<n; j++) {
				// System.out.print(dat[j][i]);
				if (dat[j][i] == 1)
					ct++;
			}
			c1[i] = ct;
			// System.out.println();
			System.out.println(c1[i]);
		}

	}
}