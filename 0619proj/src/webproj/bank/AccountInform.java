package webproj.bank;

public class AccountInform {
	
	private int mem_id;				// PK
	private String mem_name;		// ����
	private String mem_accountnum;	// ���¹�ȣ
	private String mem_birth;		// �� �������
	
	/*
		Generate getter and setter
	 	������ �ְ� �޴� ���.
	*/
	
	public int getMem_id() {
		return mem_id;
	}
	public void setMem_id(int mem_id) {
		this.mem_id = mem_id;
	}
	public String getMem_name() {
		return mem_name;
	}
	public void setMem_name(String mem_name) {
		this.mem_name = mem_name;
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
	
}
