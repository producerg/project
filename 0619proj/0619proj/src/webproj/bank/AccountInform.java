package webproj.bank;

public class AccountInform {
	
	private String mem_id;			// PK
	private String mem_name;		// 고객명
	private String mem_accid;		// 로그인용 계정 id			
	private String mem_accountnum;	// 계좌번호
	private String mem_birth;		// 고객 생년월일
	private int mem_bank;			// 계좌가 속한 은행명
	private int mem_curranc;		// 가진 금액
	private String mem_passwd;		// 고객의 계좌 비밀번호
	private String mem_paypasswd;	// 결제(송금) 비밀번호
	
	/*
		Generate getter and setter
	 	데이터 주고 받는 통로.
	*/
	
	public String getMem_id() {
		return mem_id;
	}
	public void setMem_id(String mem_id) {
		this.mem_id = mem_id;
	}
	public String getMem_name() {
		return mem_name;
	}
	public void setMem_name(String mem_name) {
		this.mem_name = mem_name;
	}
	public String getMem_accid() {
		return mem_accid;
	}
	public void setMem_accid(String mem_accid) {
		this.mem_accid = mem_accid;
	}
	public String getMem_accountnum() {
		return mem_accountnum;
	}
	public void setMem_accountnum(String mem_accountnum) {
		this.mem_accountnum = mem_accountnum;
	}
	public String getMem_birth() {
		return mem_birth;
	}
	public void setMem_birth(String mem_birth) {
		this.mem_birth = mem_birth;
	}
	public int getMem_bank() {
		return mem_bank;
	}
	public void setMem_bank(int mem_bank) {
		this.mem_bank = mem_bank;
	}
	public int getMem_curranc() {
		return mem_curranc;
	}
	public void setMem_curranc(int mem_curranc) {
		this.mem_curranc = mem_curranc;
	}
	public String getMem_passwd() {
		return mem_passwd;
	}
	public void setMem_passwd(String mem_passwd) {
		this.mem_passwd = mem_passwd;
	}
	public String getMem_paypasswd() {
		return mem_paypasswd;
	}
	public void setMem_paypasswd(String mem_paypasswd) {
		this.mem_paypasswd = mem_paypasswd;
	}

}
