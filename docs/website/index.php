<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

require_once ("tools/tools.php");

$latest_version = 13;
$latest_release = 12;

// Language
if (isset($_GET['lan']))
  $_COOKIE['lan'] = $_GET['lan'];
$language = ["fr", "en"];
if (!isset($_COOKIE['lan']) || !in_array($_COOKIE['lan'], $language))
  $language = "fr";
else
{
  $language = $_COOKIE['lan'];
  setcookie("lan", $language, time() + 60 * 60 * 24 * 365);
}
require_once ("$language.php");

// Ads
if (isset($_POST['ads'])
    && filter_chars($_POST['ads'], "abcdefghijklmnopqrstuvwxyz_"))
{
  $ads = $_POST['ads'];
  setcookie("ads", $ads, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['ads'])
    || !filter_chars($_COOKIE['ads'], "abcdefghijklmnopqrstuvwxyz_"))
  $ads = "ads";
else
  $ads = $_COOKIE['ads'];

// Learning circle
if (isset($_POST['circle']))
{
  $circle = (int)$_POST['circle'];
  setcookie("circle", $circle, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['circle']))
  $circle = 50;
else
  $circle = (int)$_COOKIE['circle'];

// Learning circle
if (isset($_POST['version']))
{
  $version = (int)$_POST['version'];
  setcookie("version", $version, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['version']))
  $version = $latest_version;
else
  $version = (int)$_COOKIE['version'];

// Theme
if (isset($_POST['theme'])
    && filter_chars($_POST['theme'], "abcdefghijklmnopqrstuvwxyz_"))
{
  $theme = $_POST['theme'];
  setcookie("theme", $theme, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['theme'])
    || !filter_chars($_COOKIE['theme'], "abcdefghijklmnopqrstuvwxyz_"))
  $theme = "theme_granit";
else
  $theme = $_COOKIE['theme'];
if (file_exists("./style/$theme.css") == false)
  $theme = "theme_granit";

if (!isset($_COOKIE["first_visit"]))
  setcookie("first_visit", "1", time() + 60 * 60 * 24 * 365);

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <!--   __________________________________________________________________
    ----  /                                                                 /\
    ---- /_________________________________________________________________/  \
    ----  \////////////////////////////////////////////////////////////////\   \
    ----   \/////     //     //      //     //     //     ///\/////       //\   \
    ----    \///_____//_____//__  __//_____//_____//_____///  \_//_______////\   \
    ----     \//\    \ \    \ \ \_\ \ \    \ |    \ \  /   \ /  \   \\  \/////\   \
    ----      \//\    \ \____\ \    /\ \    \ \    \ \_____/\____\   \\  \____/\   \
    ----       \//\  / \/\  //\ \  ///\ \  / \/\    \///   \ \  //\  / \ /   ///\   \
    ----        \//\___|//\////\/\/////\/\___|//\___|//_____\/\////\/___\___/////\  /
    ----         \________________________________________________________________\/
    ----
    ---- Jason Brillante "Damdoshi"
    ----   Hanged Bunny Studio 2014-<?=date("Y", time()); ?>
    ----
    ----     La  Caverne  Aux  Lapins  Noirs - LibLapin
    --->
    <title>LibLapin</title>
    <meta
        name="description"
        content="<?=htmlentities(file_get_contents("$language/description.htm")); ?>"
    />
    <link rel="stylesheet" href="style/neutralize.css" />
    <link rel="stylesheet" href="style/structure.css" />
    <link rel="stylesheet" href="style/<?=$theme; ?>.css" />
    <?php
    foreach (scandir("js/") as $file)
    {
      if ($file[0] != "." && $file[strlen($file) - 1] != "~")
      {
    ?>
      <script type="text/javascript" src="js/<?=$file; ?>"></script>
    <?php
      }
    }
    ?>
  </head>
  <?php if (isset($_COOKIE["first_visit"])) { ?>
  <body onLoad="Reveal('Cover');">
    <div id="Cover">
  <?php } else { ?>
  <body>
    <div id="Cover" onClick="Reveal('Cover');">
  <?php } ?>
      <img src="res/coverlogo.png" alt="..." id="LoadingLogo" />
      <script type="text/javascript">
       LogoDance('Cover', 'LoadingLogo');
      </script>
      <?php
      // First visit
      if (!isset($_COOKIE["first_visit"]))
      {
        echo "<p><br />$FirstVisitMessage<br /><br /></p>";
      }
      ?>
    </div>

    <header>
      <a href="index.php">
        <div>
          <img src="res/bigbunny.png" alt="LibLapin's logo" />
        </div>
      </a>
      <a href="index.php"><h1>LibLapin</h1></a>
      <div class="HeaderOverlay">
      </div>
    </header>

    <nav>
      <div class="HeaderOverlay">
        <a href="index.php?pag=0">
          <div><?=$MainPage; ?></div>
        </a>
        <a href="index.php?pag=1">
          <div><?=$Tutorials; ?></div>
        </a>
        <a href="index.php?pag=2">
          <div><?=$Manuals; ?></div>
        </a>
        <a href="index.php?pag=3">
          <div><?=$Download; ?></div>
        </a>
        <a href="index.php?pag=5">
          <div><?=$Gallery; ?></div>
        </a>
      </div>
    </nav>

    <div id="Body">
      <?php
      $page = [
        "main.php",
        "tuto.php",
        "manual.php",
        "download.php",
        "docpage.php",
        "gallery.php"
      ];
      if (!isset($_GET['pag']) || (int)$_GET['pag'] < 0 || (int)$_GET['pag'] >= count($page))
        $_GET['pag'] = 0;
      require_once ($page[(int)$_GET['pag']]);
      ?>
    </div>

    <footer>
      <form method="post" class="style">
        <select name="theme" onChange="this.form.submit();">
          <?php
          foreach(scandir("./style/") as $css)
          {
            if (strncmp($css, "theme_", 6) == 0
                && strstr($css, ".css") != false
                && $css[strlen($css) - 1] != -1)
            {
              $css = str_replace(".css", "", $css);
              $name = substr($css, 6);
          ?>
            <option
                value="<?=$css; ?>"
                <?=$theme == $css ? "selected" : ""; ?>
            >
              Style: <?=pretty_name($name); ?>
            </option>
          <?php
            }
          }
          ?>
        </select>
      </form>
      <form method="post" class="style">
        <select name="ads" onChange="this.form.submit();">
          <option value="ads" <?=$ads == "ads" ? "selected" : ""; ?>>Ads</option>
          <option value="no_ads" <?=$ads == "no_ads" ? "selected" : ""; ?>>No ads</option>
        </select>
      </form>
      <form method="post" class="style">
        <label for="circle">
          <?=$UserLevel; ?>
        </label>
        <select name="circle" onChange="this.form.submit();">
          <?php
          $rings = [
            00 => "Beginner's manual",
            10 => "Rookie's manual",
            20 => "Intermediate's manual",
            30 => "Skillful's manual",
            40 => "Expert's manual",
            50 => "Full manual",
          ];
          foreach ($rings as $k => $v) {
          ?>
            <option value="<?=$k; ?>" <?=$k == $circle ? "selected" : ""; ?>>
              <?=$LevelRing[$v]; ?>
            </option>
          <?php } ?>
        </select>
      </form>
      <form method="post" class="style">
        <label for="version">
          <?=$LibraryVersion; ?>
        </label>
        <select name="version" onChange="this.form.submit();">
          <?php
          for ($i = $latest_version; $i >= 0; --$i) {
          ?>
            <option value="<?=$i; ?>" <?=$i == $version ? "selected" : ""; ?>>
              1.<?=$i ?>
              <?php if ($i == $latest_release) echo "(".$LatestVersion.")"; ?>
              <?php if ($i == 9) echo "(".$LastEpitechVersion.")"; ?>
              <?php if ($i == 2) echo "(".$FirstEpitechVersion.")"; ?>
            </option>
          <?php } ?>
          <option value="-1" <?=$version == "-1" ? "selected" : "" ?>>
            <?=$DisplayAllSymbols; ?>
          </option>
        </select>
      </form>

      Hanged Bunny Studio 2014-<?=date("Y"); ?>

      <a href="index.php?lan=fr">
        <div class="language">
          <img src="res/fr.png" alt="Francais" />
        </div>
      </a>
      <a href="index.php?lan=en">
        <div class="language">
          <img src="res/en.png" alt="Anglais" />
        </div>
      </a>
    </footer>
  </body>
</html>
