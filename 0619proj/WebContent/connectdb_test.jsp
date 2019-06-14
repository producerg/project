<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import = "java.sql.*" %>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<%
	Connection conn = null;		// 디비 연동 자체에  필요한 객체
	Statement stmt = null;		// 문장 실행에 필요한 객체
	ResultSet rs = null;		// 결과 레코드 출력 객체
	
	String url = "jdbc:oracle:thin:@localhost:1521:orcl";
	String user_id = "USER";
	String user_passwd = "1234";
	String sql = "SELECT * FROM member";
	/*
		sql String 변수는 쿼리문 여기다 담을 변수임.
		지금은 일단 임의의 table를 조회하는 문장을 집어넣음.
	*/
%>
<%
	/*
		try-catch-finally 구문으로 db 연동 최종 완성함.
	*/
%>
</body>
</html>