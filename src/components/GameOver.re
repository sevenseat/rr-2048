[%bs.raw {|require('./GameOver.css')|}];

let component = ReasonReact.statelessComponent("Result");

let make = (~gameOver, ~score, ~onReplay, _) => {
  ...component,
  render: (_self) =>
    switch gameOver {
    | false => ReasonReact.nullElement
    | true =>
      <div className="end_layer">
        <div className="message"> (ReasonReact.stringToElement("Game Over!")) </div>
        <div className="scoreArea center">
          <div className="scoreAreaInner center">
            <div className="scoreLabel"> (ReasonReact.stringToElement("Score")) </div>
            <div className="score"> (ReasonReact.stringToElement(string_of_int(score))) </div>
          </div>
        </div>
        <div className="to_github">
          <a className="github_link" href="https://github.com/sevenseat/rr-2048">
            (ReasonReact.stringToElement("Star this project on github"))
          </a>
        </div>
        <div className="replay">
          <button className="replay-button" id="replay" onClick=onReplay>
            (ReasonReact.stringToElement("Try again"))
          </button>
        </div>
      </div>
    }
};
