const char indexpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
 <head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
  <meta charset='utf-8'>
  
  <style>
    body {font-size:100%;} 
    #main {display: table; margin: auto;  padding: 0 10px 0 10px; } 
    h2 {text-align:center; } 
    p { text-align:center; }
  </style>

	<script>
	
	</script>
  <title>GPS</title>
 </head>
 <body style="background-color: #f4f0bb;">
	<table style="border-collapse: collapse; width: 60%; height: 14px; margin-left: auto; margin-right: auto;" border="0">
  <tbody>
    <tr style="height: 14px;">
      <td style="width: 32.5665%; text-align: center; height: 14px;">
       <h3><strong><span style="font-size: 18pt;"><em>GPS</em></span><br /></strong></h3>
      </td>
    </tr>
  </tbody>
	<p>&nbsp;</p>
	<table style="border-collapse: collapse; width: 60%; height: 206px; margin-left: auto; margin-right: auto;" border="1">
		<tbody>
			<tr>
				<td style="width: 100%; text-align: center;"></td>
			</tr>
			<tr>
				<td style="width: 100%; text-align: center;"><a href="/start">Iniciar mapeo</a></td>
			</tr>
			<tr>
				<td style="width: 100%; text-align: center;"><a href="/view">Datos simples</a></td>
			</tr>
			<tr>
				<td style="width: 20%; text-align: center;">Buscar destino</td>
			</tr>
		</tbody>
	</table>
</body>
</html>

)=====";