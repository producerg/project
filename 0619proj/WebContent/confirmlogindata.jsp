<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!-- 자바빈즈 사용 -->
<%@ page import="webproj.bank.*" %>

<jsp:useBean id="customer" class="webproj.bank.AccountInform" scope="session"/>
<jsp:setProperty name="customer" property="*"/>
<% request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>1인프로젝트함</title>
</head>
<body>
<!-- 
	여기서 사용자 데이터 넘어옴.
 -->
<%
	// 예제용 사용자 및 비밀번호 목록.
	// String 배열에 쿼리문으로 유저들 계정 id, 계정 로그인 용 비밀번호 받아 와야 함.
	boolean result = false;
	int log_flag = 0;

	//
	String mem_accid = request.getParameter("mem_accid");
	String mem_passwd = request.getParameter("mem_passwd");
	
	if(mem_accid==null || mem_accid.equals("")) {	// id값이 없는 경우.
		out.println("<script>alert('id 입력이 없습니다.');history.back()</script>");
	}
	// 사용자 인증 단계
	String redirectUrl = "logout.jsp";
	// 인증 실패 시 재요청 될 URL
	
	AccinformBean accountBean = new AccinformBean();
	log_flag = accountBean.loginCheck(customer);
	
	// 계속 이용되어야 할 데이터들을 세션에 담기 위한 변수 선언
	String custid = accountBean.customerName(customer);
	String customerPayPasswd = accountBean.customerPayPasswd(customer);
	String customerAccountNum = accountBean.customerAccountNum(customer);
	String customerPrimaryId = accountBean.customerPrimaryId(customer);
	// cus..primaryid : pk 값으로 집어넣어서 고유값 확인해야 하므로 집어넣음.
	int customerDeposit = accountBean.customerDeposit(customer);
	
	// 로그인 값 판정을 위한 플래그
	// 자바빈즈단으로 보내고 받아온 플래그로 로그인 성공 여부를 판정.
	if(log_flag == 1) {
		session.setAttribute("loggeduser", mem_accid);
		// loggeduser는 보안 용도를 위해, 이 세션이 없으면 못 넘어가게 만듬.
		// 로그인 성공하면 이용해야 할 정보들 세션값으로 쫙 넘김.
		session.setAttribute("username", custid);
		session.setAttribute("useraccnum", customerAccountNum);
		session.setAttribute("userpaypasswd",customerPayPasswd);
		session.setAttribute("customerpk",customerPrimaryId);
		session.setAttribute("deposit",customerDeposit);
		redirectUrl = "userloged_mainscreen.jsp";
	} else {
		out.println("응 잘가");
		out.println("<script>alert('로그인 실패');history.back()</script>");
	}
	System.out.println(log_flag);
	// 로그인이 성공하면 여기서

	response.sendRedirect(redirectUrl);
%>
</body>
</html>