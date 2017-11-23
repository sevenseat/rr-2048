let component = ReasonReact.statelessComponent("EventLayer");

let make = (~onAction, ~className=?, children) => {
  let keyDown = (event) =>
    GameLogic.(
      switch (ReactEventRe.Keyboard.which(event)) {
      | 37 => onAction(Left)
      | 38 => onAction(Up)
      | 39 => onAction(Right)
      | 40 => onAction(Down)
      | _ => ()
      }
    );
  {
    ...component,
    render: (_self) =>
      /* <div onKeyDown=keyDown tabIndex=0> ReasonReact.arrayToElement children </div> */
      ReasonReact.createDomElement(
        "div",
        ~props={"onKeyDown": keyDown, "className": className, "tabIndex": 0},
        children
      )
  }
};