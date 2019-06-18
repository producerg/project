<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%
		session.invalidate();
		// invalidate()로 세션 정보 깔끔히 버림.
		response.sendRedirect("thebank_mainscreen.jsp");
	%>
</body>
</html>
