<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:template match="/sproject">
    <html>
      <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
        <title><xsl:value-of select="//code"/> - <xsl:value-of select="//aname"/> (<xsl:value-of select="//uname"/>) </title> 
<!-- pro vdalene nasazeni -->
<!--         <link rel="stylesheet" type="text/css" href="https://users.fit.cvut.cz/~valenta/BI-DBS/sprojekt/sprojekt_html.css"/> -->
<!-- pro lokalni testovani -->
        <link rel="stylesheet" type="text/css" href="./sproject_html.css"/>
      </head>

      <body>

<!-- Java script pro vypnuti/zapnuti zobrazeni komentaru -->
<script type="text/javascript" >
var display=0;
function noComment(){
var comments=document.getElementsByName("comment");
if(display==1){
	set_to='block';
	display=0;
}
else{
	set_to='none';
	display=1;
};
for (i in comments){
	el=comments[i].style; 
	el.display=set_to;
}
return false;
}
</script>

<input type="button" value=" Vypnout / zapnout zobrazeni komentaru" onClick="return noComment();"/>

<!-- Informace o kurzu -->
        <h3 class="course">
          <xsl:value-of select="//code"/> -            <xsl:value-of select="//cname"/>,            <xsl:value-of select="//semester"/>
        </h3>

<!-- Informace o autorovi -->
        <h3 class="author">
          <xsl:value-of select="//aname"/> ( <xsl:value-of select="//uname"/> )          <xsl:value-of select="//seminar"/>
        </h3>
        <h4 class="author">
         <xsl:element name="a">
		<xsl:attribute name ="href">
			mailto:<xsl:value-of select="//email"/>
               </xsl:attribute>
              <xsl:value-of select="//email"/>
	   </xsl:element>
        </h4>

<!-- Deklarace -->
        <p class="declaration">
          <xsl:value-of select="//declaration"/>
        </p>

<!-- Nazev semestralky -->
        <h1>
          <xsl:value-of select="//content/title"/>
        </h1>

<!-- Popis -->
        <h2>
          <xsl:value-of select="//description/title"/>
        </h2>
        <xsl:for-each select="//description/*">
 		 <xsl:if test="local-name()='para'"> 
			<p> <xsl:apply-templates mode="moje_para"/> </p>
		 </xsl:if>
		<xsl:if test="local-name()='comment'">
			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
		</xsl:if> 
        </xsl:for-each>
<!-- Datovy model -->
        <h2>
          <xsl:value-of select="//data_model/title"/>
        </h2>

         <xsl:element name="img">
		<xsl:attribute name ="src">
			<xsl:value-of select="//dm_picture//imagedata/@fileref"/>
               </xsl:attribute>
		<xsl:attribute name ="alt">
			Zde má být obrázek vašeho konceptuálního modelu.
               </xsl:attribute>
	   </xsl:element>

	<xsl:for-each select="//data_model/comment">
		<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>	
	</xsl:for-each>
	
         <xsl:for-each select="//dm_discussion/*">
 		 <xsl:if test="local-name()='para'"> 
			<p> <xsl:apply-templates mode="moje_para"/> </p>
		 </xsl:if>
		<xsl:if test="local-name()='comment'">
			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
		</xsl:if> 
        </xsl:for-each>

<!-- Relacni model, je to nepovinny element, proto kontorola, da je pritomen -->
        <xsl:if test="//relational_model != ''">
        <h2>
          <xsl:value-of select="//relational_model/title"/>
        </h2>

         <xsl:element name="img">
		<xsl:attribute name ="src">
			<xsl:value-of select="//rm_picture//imagedata/@fileref"/>
               </xsl:attribute>
		<xsl:attribute name ="alt">
			Zde má být obrázek vašeho relačního modelu.
               </xsl:attribute>
	   </xsl:element>

	<xsl:for-each select="//relational_model/comment">
		<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>	
	</xsl:for-each>
	
         <xsl:for-each select="//rm_discussion/*">
 		 <xsl:if test="local-name()='para'"> 
			<p> <xsl:apply-templates mode="moje_para"/> </p>
		 </xsl:if>
		<xsl:if test="local-name()='comment'">
			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
		</xsl:if> 
        </xsl:for-each>
        </xsl:if>


<!-- SQL prikazy -->
        <h2>
          <xsl:value-of select="//queries/title"/>
        </h2>
         <ol>
        	<xsl:for-each select="//queries/dotazy/dotaz">
         	<li>
                <p> Kód dotazu: <b><a name="{@dotaz_id}"><xsl:value-of select="@dotaz_id"/></a></b> <a href="#tabulka_pokryti"> [Tabulka pokryti kategorií SQL příkazů]</a></p>
		<xsl:for-each select="./*">
			<xsl:if test="local-name()='popis_dotazu'">
				<xsl:for-each select="./para">
		 			<p> <xsl:apply-templates mode="moje_para"/> </p>
				</xsl:for-each>
			</xsl:if>
			<xsl:if test="local-name()='comment'">
				<xsl:for-each select=".">
		 			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
				</xsl:for-each>
			</xsl:if>
			<xsl:if test="local-name()='relacni_algebra'">
				<xsl:for-each select=".">
		 			<p class="ra"> <xsl:apply-templates mode="moje_para"/> </p>
				</xsl:for-each>
			</xsl:if>
			<xsl:if test="local-name()='sql'">
				<xsl:for-each select=".">
		 			<p class="sql"> <xsl:apply-templates mode="moje_para"/> </p>
				</xsl:for-each>
			</xsl:if>
		</xsl:for-each>
        	</li>
		</xsl:for-each>
        </ol>
	<!-- Tabulka pokryti SQL prikazu -->
	<h2> <a name="tabulka_pokryti"> Tabulka pokrytí kategorií SQL příkazů </a></h2>
   	<table>
	<tbody>
	<tr>
		<th> Kategorie </th>
		<th> Kódy porývajících dotazů</th>
		<th> Charekteristika kategorie příkazu</th>
	</tr>
		<xsl:for-each select="//queries/pokryti_dotazu/radek">
			<tr>
			   <td><xsl:value-of select="./kategorie"/></td>
			   <td>
                             <xsl:for-each select="./odkazy/link">
                                <a href="{@url}"><xsl:value-of select="."/> </a> <xsl:text> </xsl:text>
                             </xsl:for-each>
			   </td>
			   <td><xsl:value-of select="./kategorie_popis"/></td>
			</tr>
		</xsl:for-each>
	</tbody>
	</table>

	<xsl:for-each select="//queries/comment">
		<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>	
	</xsl:for-each>

<!-- Skripty -->
        <h2>
          <xsl:value-of select="//scripts/title"/>
        </h2>
        <xsl:for-each select="//scripts/*">
 		 <xsl:if test="local-name()='para'"> 
			<p> <xsl:apply-templates mode="moje_para"/> </p>
		 </xsl:if>
		<xsl:if test="local-name()='comment'">
			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
		</xsl:if> 
        </xsl:for-each>

<!-- Zaver -->
        <h2>
          <xsl:value-of select="//conclussions/title"/>
        </h2>
        <xsl:for-each select="//conclussions/*">
 		 <xsl:if test="local-name()='para'"> 
			<p> <xsl:apply-templates mode="moje_para"/> </p>
		 </xsl:if>
		<xsl:if test="local-name()='comment'">
			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
		</xsl:if> 
        </xsl:for-each>

<!-- Odkazy -->
        <h2>
          <xsl:value-of select="//references/title"/>
        </h2>
        <xsl:for-each select="//references/*">
 		 <xsl:if test="local-name()='para'"> 
			<p> <xsl:apply-templates mode="moje_para"/> </p>
		 </xsl:if>
		<xsl:if test="local-name()='comment'">
			<p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/> </p>
		</xsl:if> 
        </xsl:for-each>

       </body>
    </html>
</xsl:template>

<!-- Nasledujici 2 templates resi mixec content v elementu para  a comment-->
<xsl:template match="*" mode="moje_para">
  <xsl:copy>
   <xsl:copy-of select="@*"/>
   <xsl:apply-templates mode="moje_para"/>
  </xsl:copy>
</xsl:template>

<xsl:template match="link" mode="moje_para">
  <a href="{@url}">
   <xsl:apply-templates mode="moje_para"/>
  </a>
</xsl:template>

<xsl:template match="para" mode="para">
  <p> <xsl:apply-templates mode="moje_para"/></p>
</xsl:template>

<xsl:template match="comment" mode="comment">
  <p class="comment" name="comment"> <xsl:apply-templates mode="moje_para"/></p>
</xsl:template>

</xsl:stylesheet>