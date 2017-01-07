<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!--  
Vstupem je dokument (Semestralka z DBS) dle:
https://users.fit.cvut.cz/~valenta/bi-dbs/sprojekt/sprojekt.dtd

       Vystupem je SQL skript, ktery je nejlepsi spoustet v SQL*Plus
             vystup obsahuje pouze specifikaci SQL prikazu jako komentar a text SQL prikazu
-->

 <xsl:output method="text" encoding="UTF-8"
omit-xml-declaration="yes" cdata-section-elements="sql"
indent="yes" media-type="text/sql"/>

<xsl:template match="/sproject">
<!-- SQL prikazy -->
set pagesize 1000
set echo on
set markup html on spool on head "&lt;title&gt;<xsl:value-of select="//code"/> - <xsl:value-of select="//aname"/>(<xsl:value-of select="//uname"/>) - Výstup SQL příkazů &lt;/title&gt; &lt;style type ='text/css'&gt;&lt;!--body {background: #ffffc6} --&gt;&lt;/style&gt;" body "&lt;h2&gt;<xsl:value-of select="//code"/> - <xsl:value-of select="//seminar"/> - <xsl:value-of select="//aname"/> - Výstup SQL příkazů&lt;/h2&gt;"
spool queries-log.html

       	<xsl:for-each select="//queries/dotazy/dotaz">
          --KOD DOTAZU: <xsl:value-of select="@dotaz_id"/>
		<xsl:for-each select="./*">
			<xsl:if test="local-name()='popis_dotazu'">
				<xsl:for-each select="./para">
 <xsl:value-of select="concat('&#xD;&#xA; -- ', normalize-space(translate(.,'&#xD;&#xA;',' ')), '&#xD;&#xA;')"/>
				</xsl:for-each>
			</xsl:if>
			<xsl:if test="local-name()='sql'">
				<xsl:for-each select=".">
<xsl:value-of select="concat('&#xD;&#xA;',.,'&#xD;&#xA; &#xD;&#xA;')"/>
				</xsl:for-each>
			</xsl:if>
		</xsl:for-each>
	</xsl:for-each>
set markup html off
spool off
</xsl:template>
</xsl:stylesheet>
