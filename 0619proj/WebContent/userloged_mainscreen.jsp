<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="webproj.bank.*" %>
    <% 
    // 인증된 세션이 없으면 이 페이지는 볼수 없게 만듦.    
    if(session.getAttribute("loggeduser")==null){
    	response.sendRedirect("logout.jsp");
    	// 로그아웃 하고 다시 메인페이지로 보내버림.
    }	
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>은행 사이트 예제</title>
</head>
<jsp:useBean id="customer" scope="session" class="webproj.bank.AccountInform">
<!-- session으로 스코프 지정한 이유 : 로그인했던 세션값은 그대로 가지고 있어야 하기 때문. -->
</jsp:useBean>
<body>
	<!-- 레이아웃 정의 -->
	<table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td width=80%>
				<jsp:include page="top.jsp" flush="false"/> 
			</td>
			<td>
				<a href="logout.jsp">로그아웃</a>
				<!-- logout.jsp에 invalidate()메소드로 세션값 정리됨. -->
			</td>
		</tr>
		<tr>
			<td>
			<b><%= session.getAttribute("username") %></b> 고객님 환영합니다.
			</td>
			<td>
				<a href="accountAdmin.jsp">내 계좌 관리</a>
			</td>
		</tr>
		<tr>
			<td>
				<jsp:include page="logged_content_main.jsp" flush="false"/>
			</td>
		</tr>
		<tr>
			<td colspan=3>
				<jsp:include page="bottom_mainscreen.jsp" flush="false"/>
			</td>
		</tr>
	</table>
</body>
</html>