<div class="mandoc">
<div class="section">
<h1 id="x4e414d45">NAME</h1> <b class="name">match</b> &#8212; <span class="desc">a tool for matching strings</span></div>
<div class="section">
<h1 id="x53594e4f50534953">SYNOPSIS</h1><table class="synopsis">
<col style="width: 5.00ex;"/>
<col/>
<tbody>
<tr>
<td>
match</td>
<td>
<b class="flag">-p</b> <i class="arg">pattern</i> [<span class="opt"><b class="flag">-c</b> <i class="arg">command</i></span>] [<span class="opt"><b class="flag">-i</b></span>] [<span class="opt"><b class="flag">-m</b></span>] [<span class="opt"><b class="flag">-t</b> <i class="arg">format</i></span>] [<span class="opt"><b class="flag">-v</b></span>] <i class="arg">string ...</i></td>
</tr>
</tbody>
</table>
</div>
<div class="section">
<h1 id="x4445534352495054494f4e">DESCRIPTION</h1> <b class="name">match</b> is a small tool for matching strings.  The <i class="arg">pattern</i> is tried on each argument and if there is a match <i class="arg">command</i> is executed with the original string and a string that is created from <i class="arg">format</i>.<div class="spacer">
</div>
<b class="name">match</b> can be used for renaming files simply by specifying  <b>mv</b> as <i class="arg">command</i>.</div>
<div class="section">
<h1 id="x4f5054494f4e53">OPTIONS</h1><dl style="margin-top: 0.00em;margin-bottom: 0.00em;" class="list list-tag">
<dt class="list-tag" style="margin-top: 1.00em;">
<b class="flag">-p</b> <i class="arg">pattern</i></dt>
<dd class="list-tag" style="margin-left: 11.00ex;">
The patterns used for matching.  See <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man7/patterns.7?query=patterns&amp;sec=7">patterns(7)</a> for details on the pattern language.</dd>
<dt class="list-tag" style="margin-top: 1.00em;">
<b class="flag">-c</b> <i class="arg">command</i></dt>
<dd class="list-tag" style="margin-left: 11.00ex;">
The command to execute when <i class="arg">pattern</i> matches a string.  The command gets two arguments the matching string (source) and a new string constructed out of the target <i class="arg">format</i>:<div class="spacer">
</div>
<i class="arg">command</i> <i class="arg">source</i> <i class="arg">target</i></dd>
<dt class="list-tag" style="margin-top: 1.00em;">
<b class="flag">-i</b></dt>
<dd class="list-tag" style="margin-left: 11.00ex;">
Ignore errors encountered while running <i class="arg">command</i>.</dd>
<dt class="list-tag" style="margin-top: 1.00em;">
<b class="flag">-m</b></dt>
<dd class="list-tag" style="margin-left: 11.00ex;">
Pass only the original string to <i class="arg">command</i>. Useful if you just want to see which strings match the given pattern.</dd>
<dt class="list-tag" style="margin-top: 1.00em;">
<b class="flag">-t</b> <i class="arg">format</i></dt>
<dd class="list-tag" style="margin-left: 11.00ex;">
Target format.  <b>%n</b> will be replaced by the n-th capture from the pattern.  Defaults to  <b>%0</b> i.e. the whole matching string.</dd>
<dt class="list-tag" style="margin-top: 1.00em;">
<b class="flag">-v</b></dt>
<dd class="list-tag" style="margin-left: 11.00ex;">
Warn on encountering non matching arguments.</dd>
</dl>
</div>
<div class="section">
<h1 id="x4558414d504c4553">EXAMPLES</h1> Rename all files like '123 - foo.jpg' to 'foo.jpg' in the current directory<div class="spacer">
</div>
<pre style="margin-left: 5.00ex;" class="lit display">
match -p '%d+% %-% ([%a%p]+)' -c mv -t %1 *</pre>
<div class="spacer">
</div>
<b>%1</b> is replaced by the first capture defined by the parentheses in the pattern.</div>
<div class="section">
<h1 id="x53454520414c534f">SEE ALSO</h1> <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man1/cp.1?query=cp&amp;sec=1">cp(1)</a> <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man1/ln.1?query=ln&amp;sec=1">ln(1)</a> <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man1/mv.1?query=mv&amp;sec=1">mv(1)</a> <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man7/patterns.7?query=patterns&amp;sec=7">patterns(7)</a> <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man8/httpd.8?query=httpd&amp;sec=8">httpd(8)</a></div>
<div class="section">
<h1 id="x415554484f5253">AUTHORS</h1> <span class="author">Tobias Kortkamp</span> &lt;<a class="link-mail" href="mailto:t@tobik.me">t@tobik.me</a>&gt;<div class="spacer">
</div>
<b class="name">match</b> uses the pattern matching engine from OpenBSD's httpd, which does all the hard work and is derived from the original implementation of the Lua scripting language written by <span class="author">Roberto Ierusalimschy</span>, <span class="author">Waldemar Celes</span>, and <span class="author">Luiz Henrique de Figueiredo</span> at PUC-Rio. It was turned into a native C API for <a class="link-man" href="http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man8/httpd.8?query=httpd&amp;sec=8">httpd(8)</a> by <span class="author">Reyk Floeter</span> &lt;<a class="link-mail" href="mailto:reyk@openbsd.org">reyk@openbsd.org</a>&gt;.</div>
</div>

