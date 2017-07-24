<table class="head">
  <tr>
    <td class="head-ltitle">PATMAT(1)</td>
    <td class="head-vol">FreeBSD General Commands Manual</td>
    <td class="head-rtitle">PATMAT(1)</td>
  </tr>
</table>
<div class="manual-text">
<h1 class="Sh" title="Sh" id="NAME"><a class="selflink" href="#NAME">NAME</a></h1>
<b class="Nm" title="Nm">patmat</b> &#8212; <span class="Nd" title="Nd">a
  pattern matching tool</span>
<h1 class="Sh" title="Sh" id="SYNOPSIS"><a class="selflink" href="#SYNOPSIS">SYNOPSIS</a></h1>
<table class="Nm">
  <tr>
    <td><b class="Nm" title="Nm">patmat</b></td>
    <td><b class="Fl" title="Fl">-p</b> <var class="Ar" title="Ar">pattern</var>
      [<span class="Op"><b class="Fl" title="Fl">-c</b>
      <var class="Ar" title="Ar">command</var></span>]
      [<span class="Op"><b class="Fl" title="Fl">-i</b></span>]
      [<span class="Op"><b class="Fl" title="Fl">-f</b>
      <var class="Ar" title="Ar">separator</var></span>]
      [<span class="Op"><b class="Fl" title="Fl">-t</b>
      <var class="Ar" title="Ar">format</var></span>]
      [<span class="Op"><b class="Fl" title="Fl">-v</b></span>]
      [<span class="Op"><var class="Ar" title="Ar">string ...</var></span>]</td>
  </tr>
</table>
<h1 class="Sh" title="Sh" id="DESCRIPTION"><a class="selflink" href="#DESCRIPTION">DESCRIPTION</a></h1>
<b class="Nm" title="Nm">patmat</b> is a small tool for matching strings. The
  <var class="Ar" title="Ar">pattern</var> is tried on each string and if there
  is a match <var class="Ar" title="Ar">command</var> is executed with the
  original string and a string that is created from
  <var class="Ar" title="Ar">format</var>.
<div class="Pp"></div>
<b class="Nm" title="Nm">patmat</b> will match on lines read from stdin if no
  string arguments are passed to it.
<h1 class="Sh" title="Sh" id="OPTIONS"><a class="selflink" href="#OPTIONS">OPTIONS</a></h1>
<dl class="Bl-tag" style="margin-left: 16.20ex;">
  <dt class="It-tag" style="margin-left: -16.20ex;"><a class="selflink" href="#p"><b class="Fl" title="Fl" id="p">-p</b></a>
    <var class="Ar" title="Ar">pattern</var></dt>
  <dd class="It-tag">The patterns used for matching. See
      <a class="Xr" title="Xr">patmat-patterns(7)</a> for details on the pattern
      language.</dd>
  <dt class="It-tag" style="margin-left: -16.20ex;"><a class="selflink" href="#c"><b class="Fl" title="Fl" id="c">-c</b></a>
    <var class="Ar" title="Ar">script</var></dt>
  <dd class="It-tag">The script to execute when
      <var class="Ar" title="Ar">pattern</var> matches a string.
      <var class="Ar" title="Ar">script</var> is passed to
      <i class="Pa" title="Pa">/bin/sh</i>. In the script the matching string
      (source) and a new string constructed out of the target format will be
      available as $1 and $2 respectively.
    <div class="Pp"></div>
    If <b class="Fl" title="Fl">-c</b> is not specified, the source and target
      will be printed to stdout separated by a tab (\t) or the string specified
      with <b class="Fl" title="Fl">-f</b>.</dd>
  <dt class="It-tag" style="margin-left: -16.20ex;"><a class="selflink" href="#f"><b class="Fl" title="Fl" id="f">-f</b></a></dt>
  <dd class="It-tag">Set to change the string used as separator for source and
      target. By default a tab is used. This option is ignored when
      <b class="Fl" title="Fl">-c</b> is used.</dd>
  <dt class="It-tag" style="margin-left: -16.20ex;"><a class="selflink" href="#i"><b class="Fl" title="Fl" id="i">-i</b></a></dt>
  <dd class="It-tag">Ignore errors encountered while running
      <var class="Ar" title="Ar">script</var>. By default
      <b class="Nm" title="Nm">patmat</b> will terminate when the script fails
      to run. This option is ignored when <b class="Fl" title="Fl">-c</b> is not
      used.</dd>
  <dt class="It-tag" style="margin-left: -16.20ex;"><a class="selflink" href="#t"><b class="Fl" title="Fl" id="t">-t</b></a>
    <var class="Ar" title="Ar">format</var></dt>
  <dd class="It-tag">Target format. <b>%n</b> will be replaced by the n-th
      capture from the pattern. Defaults to <b>%0</b> i.e. the whole matching
      string.</dd>
  <dt class="It-tag" style="margin-left: -16.20ex;"><a class="selflink" href="#v"><b class="Fl" title="Fl" id="v">-v</b></a></dt>
  <dd class="It-tag">Warn on encountering non matching arguments.</dd>
</dl>
<h1 class="Sh" title="Sh" id="EXAMPLES"><a class="selflink" href="#EXAMPLES">EXAMPLES</a></h1>
Rename all files like '123 - foo.jpg' to 'foo.jpg' in the current directory.
  <b>%1</b> is replaced by the first capture defined by the parentheses in the
  pattern.
<div class="Pp"></div>
<div class="Bd" style="margin-left: 5.00ex;">
<pre class="Li">
patmat -p '%d+% %-% ([%a%p]+)' -t %1 -c 'mv &quot;$1&quot; &quot;$2&quot;' *
</pre>
</div>
<div class="Pp"></div>
Output a CSV table with two columns: The first column will have the original
  filenames and the second column will have the filenames with a 'FreeBSD-'
  prefix and '.iso' suffix for all files in the current directory.
<div class="Pp"></div>
<div class="Bd" style="margin-left: 5.00ex;">
<pre class="Li">
patmat -p '.*' -f';' -t 'FreeBSD-%0.iso' * &gt; out.csv
</pre>
</div>
<h1 class="Sh" title="Sh" id="SEE_ALSO"><a class="selflink" href="#SEE_ALSO">SEE
  ALSO</a></h1>
<a class="Xr" title="Xr">patmat-patterns(7)</a>
<h1 class="Sh" title="Sh" id="AUTHORS"><a class="selflink" href="#AUTHORS">AUTHORS</a></h1>
<span class="An" title="An">Tobias Kortkamp</span>
  &lt;<a class="Mt" title="Mt" href="mailto:t@tobik.me">t@tobik.me</a>&gt;
<div class="Pp"></div>
<b class="Nm" title="Nm">patmat</b> uses the pattern matching engine from
  OpenBSD's httpd, which does all the hard work and is derived from the original
  implementation of the Lua scripting language written by
  <span class="An" title="An">Roberto Ierusalimschy</span>,
  <span class="An" title="An">Waldemar Celes</span>, and
  <span class="An" title="An">Luiz Henrique de Figueiredo</span> at PUC-Rio. It
  was turned into a native C API for <a class="Xr" title="Xr">httpd(8)</a> by
  <span class="An" title="An">Reyk Floeter</span>
  &lt;<a class="Mt" title="Mt" href="mailto:reyk@openbsd.org">reyk@openbsd.org</a>&gt;.</div>
<table class="foot">
  <tr>
    <td class="foot-date">July 24, 2017</td>
    <td class="foot-os">FreeBSD 12.0-CURRENT</td>
  </tr>
</table>
