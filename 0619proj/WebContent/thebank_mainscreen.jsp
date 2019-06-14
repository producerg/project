<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>은행 사이트 예제</title>
</head>
<body>
	<!-- 레이아웃 정의 -->
	<table width="100%" border="0" cellpadding="1" cellspacing="0">
		<tr>
			<td>
				<jsp:include page="top.jsp" flush="false"/>
			</td>
		</tr>
		<tr>
			<td>
				<jsp:include page="content_main.jsp" flush="false"/>
			</td>
		</tr>
		<tr>
			<td>
				<jsp:include page="bottom_mainscreen.jsp" flush="false"/>
			</td>
		</tr>
	</table>
</body>
</html>