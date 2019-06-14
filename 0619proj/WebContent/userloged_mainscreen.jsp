<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <% // 인증된 세션이 없으면 이 페이지는 볼수 없게 만듦.
    
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
<body>
	<!-- 레이아웃 정의 -->
	<table width="100%" border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td>
				<jsp:include page="top.jsp" flush="false"/> 
			</td>
			<td>
				<%= session.getAttribute("loggeduser") %> 고객님 환영합니다.
			</td>
			<td>
				<a href="logout.jsp">로그아웃</a>
			</td>
		</tr>
		<tr>
			<td>
				<jsp:include page="content_main.jsp" flush="false"/>
			</td>
			<td>
				<!-- 여기에 본인 계좌 목록 달림. -->
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