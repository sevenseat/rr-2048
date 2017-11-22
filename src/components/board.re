[%bs.raw {|require('./board.css')|}];

module Card = {
  let component = ReasonReact.statelessComponent("Card");
  let make = (~value, _children) => {
    ...component,
    render: (_self) =>
      if (value == 0) {
        <div className="card" />
      } else {
        <div className=("card card_number_" ++ string_of_int(value))>
          (ReasonReact.stringToElement(string_of_int(value)))
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
    <div className="board"> renderRows </div>
  }
};
