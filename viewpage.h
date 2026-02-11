const char viewpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta charset="utf-8" />
    <title>GPS</title>
    <style>
      * { box-sizing: border-box; }
      body {
        margin: 0;
        padding: 16px;
        font-family: Arial, Helvetica, sans-serif;
        background: #f4f0bb;
        color: #1a1a1a;
      }
      .wrap {
        max-width: 520px;
        margin: 0 auto;
      }
      .title {
        text-align: center;
        margin: 4px 0 16px 0;
        font-size: 20px;
        font-weight: 700;
      }
      .data-table {
        width: 100%;
        border-collapse: collapse;
        border: 1px solid #222;
        background: #fffbe2;
      }
      .data-table td {
        padding: 10px 8px;
        border: 1px solid #222;
        text-align: center;
        font-size: 15px;
        overflow-wrap: anywhere;
      }
      .section {
        margin-top: 18px;
      }
      .btn {
        display: block;
        width: 100%;
        max-width: 50vw;
        padding: 12px 10px;
        font-size: 16px;
        border: 1px solid #222;
        border-radius: 4px;
        background: #e8e1a6;
        color: #1a1a1a;
        text-align: center;
        text-decoration: none;
        cursor: pointer;
        margin: 0 auto;
      }
      .btn:active { background: #dbd28f; }
    </style>
  </head>
  <body>
    <div class="wrap">
      <div class="title">GPS</div>

      <table class="data-table">
        <tbody>
          <tr>
            <td>Latitud:</td>
            <td id="lat"></td>
          </tr>
          <tr>
            <td>Longitud:</td>
            <td id="long"></td>
          </tr>
          <tr>
            <td>Altitud:</td>
            <td id="alt"></td>
          </tr>
          <tr>
            <td>Sat&eacute;lites:</td>
            <td id="sats"></td>
          </tr>
          <tr>
            <td>HDOP:</td>
            <td id="hdop"></td>
          </tr>
          <tr>
            <td>Fecha/Hora:</td>
            <td id="dateTime"></td>
          </tr>
        </tbody>
      </table>

      <div class="section">
        <a class="btn" href="/">Volver al inicio</a>
      </div>
    </div>

    <script>
      setInterval(function () {
        getData();
      }, 1000);

      function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "read", true);
        xhttp.getResponseHeader("Content-type", "text/json");
        xhttp.onload = function () {
          const obj = JSON.parse(this.responseText);
          document.getElementById("lat").innerHTML = Number(obj.lat).toFixed(8);
          document.getElementById("long").innerHTML = Number(obj.long).toFixed(8);
          document.getElementById("alt").innerHTML = obj.alt;
          document.getElementById("sats").innerHTML = obj.sats;
          document.getElementById("hdop").innerHTML = obj.hdop;
          document.getElementById("dateTime").innerHTML = obj.dateTime;
        };
        xhttp.send();
      }
    </script>
  </body>
</html>

)=====";
