package webproj.bank;
import java.sql.*;
import java.util.*;
/*
 	DAO 클래스
 	DB 관련 데이터 정보 처리.
 	(여기서 송금 관련 데이터 처리)
 */
public class AccinformBean {
	Connection conn = null;
	PreparedStatement pstmt = null;
	// 빈즈 파일을 받아 올 거
	String ref_id=null;			// 로그인 할때 id 비교를 위한 정보 받아옴.
	String ref_passwd=null;		// 로그인 할때 비교를 위한 패스워드 정보 받음.

	// 오라클 연동 정보
	String jdbc_driver="oracle.jdbc.driver.OracleDriver";
	String jdbc_url="jdbc:oracle:thin:@localhost:1521:orcl";
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
	// 고객 정보 전부 다 ArrayList 하나에 받아 옴
	public ArrayList<AccountInform> getCustomerList() {
		connect();
		ArrayList<AccountInform> customerList = new ArrayList<AccountInform>();
		String sql = "SELECT * FROM customer_info";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				AccountInform customer = new AccountInform();
				customer.setMem_id(rs.getString("id"));
				customer.setMem_accid(rs.getString("mem_accid"));
				customer.setMem_accountnum(rs.getString("mem_accountnum"));
				customer.setMem_birth(rs.getString("mem_birth"));
				customer.setMem_curranc(rs.getInt("mem_curranc"));
				customer.setMem_bank(rs.getInt("mem_bank"));
				customer.setMem_name(rs.getString("mem_name"));
				customer.setMem_passwd(rs.getString("mem_passwd"));
				customer.setMem_paypasswd(rs.getString("mem_paypasswd"));
				customerList.add(customer);
			}
			rs.close();
		} catch(Exception e) {
			
		} finally {
			disconnect();
		}
		return customerList;
	}
	// 로그인 여부 판단
	public int loginCheck(AccountInform accountInform) {
		int result = 2;

		 //2 : 아이디 없음
		 //0  : 암호가 틀림
		 //1  : 아이디, 암호 일치 

		connect();
		String sql = "SELECT mem_accid, mem_passwd FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accountInform.getMem_accid());
			System.out.println(sql);
			rs = pstmt.executeQuery();
			// rs.next()=false면, result=2로 고정
			if(rs.next()) {
				String confirmPasswd = rs.getString("mem_passwd");
				if(confirmPasswd.equals(accountInform.getMem_passwd())) {
					result = 1;
				} else {
					result = 0;
				}
				rs.close();
			}
		} catch(Exception e) {
			e.printStackTrace();
		} 
		return result;
	}
	// 각 고객별 db에서의 pk값을 받아옴.
	public String customerPrimaryId(AccountInform accinform) {
		connect();
		String csPriId = null;
		String sql = "SELECT id FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accinform.getMem_accid());
			rs = pstmt.executeQuery();
			if(rs.next()) {
				csPriId = rs.getString("id");
				System.out.println(csPriId);
			}
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			disconnect();
		}
		return csPriId;
	}
	// 고갱님 정보를 쭉 긁어옴. 이 세션 데이터도 꼭 필요.
	public String customerName(AccountInform accinform) {
		connect();
		String csNameResult = null;
		String sql = "SELECT mem_name FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accinform.getMem_accid());
			rs = pstmt.executeQuery();
			if(rs.next()) {
			csNameResult = rs.getString("mem_name");
			}
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			disconnect();
		}
		return csNameResult;
	}
	// 결제에 필요한 결제 비밀번호 정보도 받아옴.
	public String customerPayPasswd(AccountInform accinform) {
		connect();
		String csPayPasswd = null;
		String sql = "SELECT mem_paypasswd FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accinform.getMem_accid());
			System.out.println(sql);
			System.out.println(accinform.getMem_accid());
			rs = pstmt.executeQuery();
			if(rs.next()) {
				csPayPasswd = rs.getString("mem_paypasswd");
				System.out.println(csPayPasswd);
			}
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			disconnect();
		}
		return csPayPasswd;
	}
	// 고객 계좌 정보에 띄울 계좌번호 정보
	public String customerAccountNum(AccountInform accinform) {
		connect();
		String csAccountNum = null;
		String sql = "SELECT mem_accountnum	FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accinform.getMem_accid());
			System.out.println(sql);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				csAccountNum = rs.getString("mem_accountnum");
				System.out.println(csAccountNum);
			}
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			disconnect();
		}
		return csAccountNum;
	}
	// 너 계좌에 지금 돈 얼마 들고 있어?
	public int customerDeposit(AccountInform accinform) {
		connect();
		int csDeposit = 0;
		String sql = "SELECT mem_curranc FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accinform.getMem_accid());
			System.out.println(sql);
			rs = pstmt.executeQuery();
			if(rs.next()) {
				csDeposit = rs.getInt("mem_curranc");
				System.out.println(csDeposit);
			}
		} catch(Exception e) {
			e.printStackTrace();
		} finally {
			disconnect();
		}
		return csDeposit;
	}
	// 계좌내역 조회
	public boolean viewAccount(AccountInform accinform) {
		connect();
		String sql = "SELECT mem_context FROM account_info;";
		try {
			pstmt = conn.prepareStatement(sql);
		} catch(Exception e) {
			e.printStackTrace();
			return false;
		} finally {
			disconnect();
		}
		return true;
	}
	// 송금 알고리즘
	public boolean sendCurrancy(AccountInform accinform) {
			connect();
			String sql;
			try {
				
			} catch(Exception e) {
				return false;
			} finally {
				disconnect();
			}
			return true;
		}	
	}
