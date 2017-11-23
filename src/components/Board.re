[%bs.raw {|require('./Board.css')|}];

module Card = {
  let component = ReasonReact.statelessComponent("Card");
  let make = (~value, _children) => {
    ...component,
    render: (_self) =>
      switch value {
      | 0 => <div className="card" />
      | value =>
        <div className={j|card card_number_$value|j}>
          (ReasonReact.stringToElement({j|$value|j}))
        </div>
      }
  };
};

let component = ReasonReact.statelessComponent("Board");

let make = (~board, _children) => {
  ...component,
  render: (_self) => {
    let renderCells = (row) =>
      List.map((value) => <div className="cell"> <Card value /> </div>, row)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    let renderRows =
      List.map((row) => <div className="row"> (renderCells(row)) </div>, board)
      |> Array.of_list
      |> ReasonReact.arrayToElement;
    <div className="game-area board"> renderRows </div>
  }
};
