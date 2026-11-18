const char indexpage[] PROGMEM = R"=====(
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
      .btn-disabled { cursor: default; }
      .note {
        text-align: center;
        font-size: 14px;
      }
    </style>
  </head>
  <body>
    <div class="wrap">
      <div class="title">GPS</div>
      <div class="section">
        <a class="btn" href="/start">Iniciar mapeo</a>
      </div>
      <div class="section">
        <a class="btn" href="/view">Datos simples</a>
      </div>
      <div class="section">
        <div class="btn btn-disabled">Buscar destino</div>
      </div>
    </div>
  </body>
</html>

)=====";
