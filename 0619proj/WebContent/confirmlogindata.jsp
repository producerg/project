<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<!-- 
	여기서 사용자 데이터 넘어옴.
 -->
<%
	// 예제용 사용자 및 비밀번호 목록.
	String [] users = {"dododh"};
	String [] passwords ={"1234"};
	/*
		테스팅용 데이터임을 유의.
	*/
	//
	String id = request.getParameter("username");
	String pw = request.getParameter("userpasswd");
	
	// 사용자 인증 단계
	String redirectUrl = "logout.jsp";
	// 인증 실패 시 재요청 될 URL
	
	/*
		만약 db 사용하면? rs.next()이용,
		while문 돌려야 함.
	*/
	for (int i=0; i< users.length; i++){
		if(users[i].equals(id) && passwords[i].equals(pw)) {
			session.setAttribute("loggeduser", id);
			// 성공 시 세션에 남김.
			redirectUrl = "userloged_mainscreen.jsp";
			// 로그인 성공 시 보낼 page.
		}	
	}
	
	response.sendRedirect(redirectUrl);
%>
</body>
</html>