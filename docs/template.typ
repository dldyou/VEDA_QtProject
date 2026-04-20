#let team_name = "13조"
#let title = "심화 실습 평가1(Qt)"
#let sub_title = "일정관리"
#let authors = (
  team_name,
  "김정운",
  "윤찬규",
)

#let head = {
  [
    #text(weight: 700)[#team_name]
    #text(weight: 400)[#sub_title]
    #h(1fr)
    #text(weight: 400)[#title]
    
    #line(length: 100%, stroke: 0.2pt)
  ]
}

#let project(title: "", authors: (), logo: none, body) = {
  set text(9pt, font: "Pretendard")
  set heading(numbering: "1.")
  set page(columns: 1, numbering: "1  /  1", number-align: center, header: head, margin: 5em)
  show outline.entry.where(level: 1): it => {
    v(25pt, weak:true)
    strong(it)
  }
  show heading : it => { it; v(0.5em);}
  
  align(center)[
    #block(text(weight: 800, 1.75em, title))
  ]
  pad(
    top: 0.5em,
    bottom: 0.5em,
    x: 2em,
    grid(
      columns: (1fr,) * calc.min(1, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(center, author)),
    ),
  )
  set par(justify: true)

  outline()

  body
}