#!/usr/bin/env python3
"""Build a readable PDF of the submitted manuscript's text, using ReportLab.

The authors' supplied 7-page formatted PDF is the layout master. This generated
PDF is a text-access copy with a clickable link to the research evidence online.
It does not pretend to preserve the original PDF's figures/layout.
"""
from html import escape
from pathlib import Path
from reportlab.lib import colors
from reportlab.lib.enums import TA_CENTER
from reportlab.lib.styles import ParagraphStyle
from reportlab.lib.pagesizes import A4
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, HRFlowable
import re

ROOT = Path(__file__).resolve().parents[1]
src = ROOT / "paper" / "AUTHOR_SUPPLIED_MANUSCRIPT_TEXT.md"
dest = ROOT / "paper" / "AI_Research_Online_Readable_Copy.pdf"
uri = "https://github.com/pulahatarafder10-del/Apple-M2-Exploratory-CPU-Study"

fontpath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
boldpath = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
pdfmetrics.registerFont(TTFont("DejaVu", fontpath))
pdfmetrics.registerFont(TTFont("DejaVuBold", boldpath))
pdfmetrics.registerFontFamily("DejaVu",normal="DejaVu",bold="DejaVuBold")

normal = ParagraphStyle("Normal", fontName="DejaVu",fontSize=9.4, leading=15,spaceAfter=7,textColor=colors.HexColor("#243040"))
smaller = ParagraphStyle("Small",parent=normal,fontSize=8.4, leading=12,textColor=colors.HexColor("#53647a"))
head = ParagraphStyle("Head",parent=normal,fontName="DejaVuBold",fontSize=13,leading=18,spaceBefore=14)
title = ParagraphStyle("Title",parent=normal,fontName="DejaVuBold",fontSize=18,leading=25,alignment=TA_CENTER,spaceAfter=18)
smalltitle = ParagraphStyle("Subtitle",parent=normal,fontName="DejaVuBold",fontSize=10,leading=16,alignment=TA_CENTER,spaceAfter=13)
def format_text(s):
    s=escape(s)
    s=re.sub(r"\*\*(.+?)\*\*",r"<b>\1</b>",s)
    s=re.sub(r"\`([^\`]+)\`",r"<font face='DejaVu'>\1</font>",s)
    return s.replace("\n"," ")
lines=src.read_text(encoding="utf8").splitlines()
story = [
    Paragraph("Inference Latency and Data Storage of Neural Networks<br/>with C++ on Apple M2",title),
    Paragraph("Pulaha Tarafder (80489) | Saket Ghosh (80564)<br/>Architecture of Computers, Vistula University, 2026/27",smalltitle),
    Paragraph("This is a readable text transcription of the authors' supplied seven-page formatted manuscript. For the original layout and charts, refer to the original PDF retained by the authors. Figures are also published in the repository.",smaller),
    Paragraph(f"Research evidence: <link href='{uri}' color='#164b8d'>{uri}</link>",normal),
    HRFlowable(width="100%",thickness=1,color=colors.HexColor("#55759f"),spaceBefore=8,spaceAfter=12)
]
# First part of source file is preface, skip it to avoid duplicating title.
start=next((i for i,s in enumerate(lines) if s.startswith("## Original PDF — Page 1")),0)
for line in lines[start:]:
    line=line.strip()
    if not line: continue
    if line.startswith("## Original PDF — Page"):
        story.append(Paragraph(format_text(line[3:]),head))
    elif re.match(r"^\d+(\.\d+)*\s+[A-Za-z]",line) and len(line)<95:
        story.append(Paragraph(format_text(line),head))
    else:
        story.append(Paragraph(format_text(line),normal))
def footer(canvas,doc):
    canvas.saveState()
    canvas.setFont("DejaVu",8)
    canvas.setFillColor(colors.HexColor("#66758a"))
    canvas.drawString(40,30,"Apple M2 exploratory CPU study · Readable online manuscript copy")
    canvas.drawRightString(A4[0]-40,30,f"Page {doc.page}")
    canvas.restoreState()
SimpleDocTemplate(str(dest),pagesize=A4,rightMargin=40,leftMargin=40,topMargin=43,bottomMargin=45,title="Apple M2 C++ inference research — readable manuscript copy").build(story,onFirstPage=footer,onLaterPages=footer)
print(f"Created {dest} ({dest.stat().st_size} bytes)")
