[%bs.raw {|require('./Title.css')|}];

let component = ReasonReact.statelessComponent("Title");

let make = (~score, ~onReplay, _children) => {
  ...component,
  render: (_self) =>
    <div className="App-header">
      <h2> (ReasonReact.stringToElement("RR 2048")) </h2>
      <div className="scoreArea">
        <div className="scoreAreaInner">
          <div className="scoreLabel"> (ReasonReact.stringToElement("Total")) </div>
          <div className="score"> (ReasonReact.stringToElement(string_of_int(score))) </div>
        </div>
      </div>
    </div>
};
