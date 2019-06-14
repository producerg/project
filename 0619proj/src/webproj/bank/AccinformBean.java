package webproj.bank;
import java.sql.*;
/*
 	DAO 클래스
 	DB 관련 데이터 정보 처리.
 	(여기서 송금 관련 데이터 처리)
 */
public class AccinformBean {
	Connection conn = null;
	PreparedStatement pstmt = null;
	// 오라클 연동 정보
	String jdbc_driver="oracle.jdbc.driver.OracleDriver";
	String jdbc_url="jdbc:oracle:thin@127.0.0.1:1521";
	// 디비 연결 설정
	void connect() {
		try {
			Class.forName(jdbc_driver);
			conn = DriverManager.getConnection(jdbc_url, "USER","1234");
			// conn 변수 테스팅용 : 본인 데이터베이스명과 비밀번호 입력해서 해보셈
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	// 디비 연결 해제
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
