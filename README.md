<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8"/>
  <style>
    table.head, table.foot { width: 100%; }
    td.head-rtitle, td.foot-os { text-align: right; }
    td.head-vol { text-align: center; }
    div.Pp { margin: 1ex 0ex; }
  </style>
  <title>PATMAT(1)</title>
</head>
<body>
<table class="head">
  <tr>
    <td class="head-ltitle">PATMAT(1)</td>
    <td class="head-vol">FreeBSD General Commands Manual</td>
    <td class="head-rtitle">PATMAT(1)</td>
  </tr>
</table>
<div class="manual-text">
<h1 class="Sh" id="NAME">NAME</h1>
<b class="Nm">patmat</b> &#8212; <span class="Nd">a tool for matching
  strings</span>
<h1 class="Sh" id="SYNOPSIS">SYNOPSIS</h1>
<table class="Nm">
  <colgroup>
    <col style="width: 6.00ex;"/>
    <col/>
  </colgroup>
  <tr>
    <td><b class="Nm">patmat</b></td>
    <td><b class="Fl">-p</b> <var class="Ar">pattern</var>
      [<span class="Op"><b class="Fl">-c</b>
      <var class="Ar">command</var></span>]
      [<span class="Op"><b class="Fl">-i</b></span>]
      [<span class="Op"><b class="Fl">-m</b></span>]
      [<span class="Op"><b class="Fl">-t</b>
      <var class="Ar">format</var></span>]
      [<span class="Op"><b class="Fl">-v</b></span>] <var class="Ar">string
      ...</var></td>
  </tr>
</table>
<h1 class="Sh" id="DESCRIPTION">DESCRIPTION</h1>
<b class="Nm">patmat</b> is a small tool for matching strings. The
  <var class="Ar">pattern</var> is tried on each argument and if there is a
  match <var class="Ar">command</var> is executed with the original string and a
  string that is created from <var class="Ar">format</var>.
<div class="Pp"></div>
<b class="Nm">patmat</b> can be used for renaming files simply by specifying
  <b>mv</b> as <var class="Ar">command</var>.
<h1 class="Sh" id="OPTIONS">OPTIONS</h1>
<dl class="Bl-tag" style="margin-left: 11.00ex;">
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-p</b>
    <var class="Ar">pattern</var></dt>
  <dd class="It-tag">The patterns used for matching. See
      <a class="Xr" href="https://man.openbsd.org/patterns.7">patterns(7)</a>
      for details on the pattern language.</dd>
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-c</b>
    <var class="Ar">command</var></dt>
  <dd class="It-tag">The command to execute when <var class="Ar">pattern</var>
      matches a string. The command gets two arguments the matching string
      (source) and a new string constructed out of the target
      <var class="Ar">format</var>:
    <div class="Pp"></div>
    <var class="Ar">command</var> <var class="Ar">source</var>
      <var class="Ar">target</var>
    <div class="Pp"></div>
    Defaults to <b>echo</b>.</dd>
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-i</b></dt>
  <dd class="It-tag">Ignore errors encountered while running
      <var class="Ar">command</var>.</dd>
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-m</b></dt>
  <dd class="It-tag">Pass only the original (source) string to
      <var class="Ar">command</var>. Use this flag if you only want see the
      strings which match the given pattern.</dd>
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-o</b></dt>
  <dd class="It-tag">Pass only the target string to
      <var class="Ar">command</var>.</dd>
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-t</b>
    <var class="Ar">format</var></dt>
  <dd class="It-tag">Target format. <b>%n</b> will be replaced by the n-th
      capture from the pattern. Defaults to <b>%0</b> i.e. the whole matching
      string.</dd>
  <dt class="It-tag" style="margin-left: -11.00ex;"><b class="Fl">-v</b></dt>
  <dd class="It-tag">Warn on encountering non matching arguments.</dd>
</dl>
<h1 class="Sh" id="EXAMPLES">EXAMPLES</h1>
Rename all files like '123 - foo.jpg' to 'foo.jpg' in the current directory
<div class="Pp"></div>
<div class="Bd" style="margin-left: 5.00ex;">
<pre class="Li">
patmat -p '%d+% %-% ([%a%p]+)' -c mv -t %1 *
</pre>
</div>
<div class="Pp"></div>
<b>%1</b> is replaced by the first capture defined by the parentheses in the
  pattern.
<h1 class="Sh" id="SEE_ALSO">SEE ALSO</h1>
<a class="Xr" href="https://man.openbsd.org/cp.1">cp(1)</a>
  <a class="Xr" href="https://man.openbsd.org/ln.1">ln(1)</a>
  <a class="Xr" href="https://man.openbsd.org/mv.1">mv(1)</a>
  <a class="Xr" href="https://man.openbsd.org/patmat-patterns.7">patmat-patterns(7)</a>
<h1 class="Sh" id="AUTHORS">AUTHORS</h1>
<span class="An">Tobias Kortkamp</span>
  &lt;<a class="Mt" href="mailto:t@tobik.me">t@tobik.me</a>&gt;
<div class="Pp"></div>
<b class="Nm">patmat</b> uses the pattern matching engine from OpenBSD's httpd,
  which does all the hard work and is derived from the original implementation
  of the Lua scripting language written by <span class="An">Roberto
  Ierusalimschy</span>, <span class="An">Waldemar Celes</span>, and
  <span class="An">Luiz Henrique de Figueiredo</span> at PUC-Rio. It was turned
  into a native C API for
  <a class="Xr" href="https://man.openbsd.org/httpd.8">httpd(8)</a> by
  <span class="An">Reyk Floeter</span>
  &lt;<a class="Mt" href="mailto:reyk@openbsd.org">reyk@openbsd.org</a>&gt;.</div>
<table class="foot">
  <tr>
    <td class="foot-date">June 28, 2015</td>
    <td class="foot-os">FreeBSD 12.0-CURRENT</td>
  </tr>
</table>
</body>
</html>
