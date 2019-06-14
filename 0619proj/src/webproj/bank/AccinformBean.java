package webproj.bank;
import java.sql.*;
/*
 	DAO Ŭ����
 	DB ���� ������ ���� ó��.
 	(���⼭ �۱� ���� ������ ó��)
 */
public class AccinformBean {
	Connection conn = null;
	PreparedStatement pstmt = null;
	// ����Ŭ ���� ����
	String jdbc_driver="oracle.jdbc.driver.OracleDriver";
	String jdbc_url="jdbc:oracle:thin@127.0.0.1:1521";
	// ��� ���� ����
	void connect() {
		try {
			Class.forName(jdbc_driver);
			conn = DriverManager.getConnection(jdbc_url, "USER","1234");
			// conn ���� �׽��ÿ� : ���� �����ͺ��̽���� ��й�ȣ �Է��ؼ� �غ���
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	// ��� ���� ����
	void disconnect() {
		if(pstmt!=null) {
			try {
				pstmt.close();
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
		if(conn!=null) {
			try {
				conn.close();
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
	
}
