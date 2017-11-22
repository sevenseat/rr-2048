type action =
  | UserEvent(GameLogic.direction)
  | Restart
  | None;

type state = {board: list(list(int))};

let component = ReasonReact.reducerComponent("App2k");

let blankBoard = [ [0,0,0,0], [0,0,0,0], [0,0,0,0], [0,0,0,0]];

let make = (_children) => {
  let keyDown = (event) =>
    switch (ReactEventRe.Keyboard.which(event)) {
    | 37 => UserEvent(GameLogic.Left)
    | 38 => UserEvent(GameLogic.Up)
    | 39 => UserEvent(GameLogic.Right)
    | 40 => UserEvent(GameLogic.Down)
    | _ => None
    };
    let genBoard = () => GameLogic.(blankBoard |> addCell |> addCell |> addCell);
  {
    ...component,
    initialState: () => {board: genBoard()},
    reducer: (action, state) =>
      switch action {
      | UserEvent(direction) =>
        ReasonReact.Update({board: GameLogic.transformBoard(direction, state.board) |> GameLogic.addCell})
      | Restart => ReasonReact.Update({board: genBoard()})
      | None => ReasonReact.NoUpdate
      },
    render: ({state, reduce}) =>
      <div onKeyDown=(reduce(keyDown)) tabIndex=0> <Board board=state.board /> </div>
  }
};
