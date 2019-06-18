package webproj.bank;
import java.sql.*;
import java.util.*;
/*
 	DAO Ŭ����
 	DB ���� ������ ���� ó��.
 	(���⼭ �۱� ���� ������ ó��)
 */
public class AccinformBean {
	Connection conn = null;
	PreparedStatement pstmt = null;
	// ���� ������ �޾� �� ��
	String ref_id=null;			// �α��� �Ҷ� id �񱳸� ���� ���� �޾ƿ�.
	String ref_passwd=null;		// �α��� �Ҷ� �񱳸� ���� �н����� ���� ����.

	// ����Ŭ ���� ����
	String jdbc_driver="oracle.jdbc.driver.OracleDriver";
	String jdbc_url="jdbc:oracle:thin:@localhost:1521:orcl";
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
	// �� ���� ���� �� ArrayList �ϳ��� �޾� ��
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
	// �α��� ���� �Ǵ�
	public int loginCheck(AccountInform accountInform) {
		int result = 2;

		 //2 : ���̵� ����
		 //0  : ��ȣ�� Ʋ��
		 //1  : ���̵�, ��ȣ ��ġ 

		connect();
		String sql = "SELECT mem_accid, mem_passwd FROM customer_info WHERE mem_accid=?";
		ResultSet rs = null;
		try {
			pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, accountInform.getMem_accid());
			System.out.println(sql);
			rs = pstmt.executeQuery();
			// rs.next()=false��, result=2�� ����
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
	// �� ���� db������ pk���� �޾ƿ�.
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
	// ���� ������ �� �ܾ��. �� ���� �����͵� �� �ʿ�.
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
	// ������ �ʿ��� ���� ��й�ȣ ������ �޾ƿ�.
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
	// �� ���� ������ ��� ���¹�ȣ ����
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
	// �� ���¿� ���� �� �� ��� �־�?
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
	// ���³��� ��ȸ
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
	// �۱� �˰���
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
