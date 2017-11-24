[%bs.raw {|require('./App2k.css')|}];

type action =
  | UserEvent(GameLogic.direction)
  | Restart;

type state = {
  board: list(list(int)),
  score: int
};

let genState = (board) => {board, score: GameLogic.scoreBoard(board)};

let component = ReasonReact.reducerComponent("App2k");

let make = (_children) => {
  ...component,
  initialState: () => genState(GameLogic.makeBoard()),
  reducer: (action, state) =>
    switch action {
    | UserEvent(direction) =>
      ReasonReact.Update(
        genState(GameLogic.transformBoard(direction, state.board) |> GameLogic.addCell)
      )
    | Restart => ReasonReact.Update(genState(GameLogic.makeBoard()))
    },
  render: ({state, reduce}) =>
    <div className="Dodo">
      <EventLayer className="App" onAction=(reduce((direction) => UserEvent(direction)))>
        <div>
          <Title score=state.score onReplay=(reduce((_event) => Restart)) />
          <div className="game-area"> <Board board=state.board /> </div>
        </div>
      </EventLayer>
    </div>
};
