[%bs.raw {|require('./Footer.css')|}];

let component = ReasonReact.statelessComponent("Notice");

let make = (_) => {
  ...component,
  render: (_self) =>
    <div className="footer">
      <p> (ReasonReact.stringToElement("Touch (mobile) / Arrow Keys (Desktop)")) </p>
      <p>
        (ReasonReact.stringToElement("Made with Reason by "))
        <a href="https://github.com/sevenseat" className="github_link">
          (ReasonReact.stringToElement("John Schweikert"))
        </a>
      </p>
      <p>
        (ReasonReact.stringToElement("Forked From "))
        <a href="https://github.com/LIU9293" className="github_link">
          (ReasonReact.stringToElement("liu kai"))
        </a>
      </p>
    </div>
};
