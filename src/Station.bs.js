// Generated by BUCKLESCRIPT VERSION 4.0.6, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.statelessComponent("WeatherStation");

function make(station, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var match = station[/* temp */2];
              return React.createElement("div", {
                          style: {
                            display: "flex",
                            alignItems: "center",
                            flexDirection: "column"
                          }
                        }, React.createElement("div", {
                              style: {
                                display: "flex",
                                alignItems: "center",
                                flexDirection: "row"
                              }
                            }, React.createElement("span", {
                                  style: {
                                    fontSize: "48px"
                                  }
                                }, match !== undefined ? Pervasives.string_of_float(match) : "No temp found"), React.createElement("span", {
                                  style: {
                                    fontSize: "24px",
                                    marginTop: "6px",
                                    alignSelf: "flex-start"
                                  }
                                }, "\xb0C"), React.createElement("img", {
                                  src: station[/* imageUrl */4]
                                })), React.createElement("span", undefined, station[/* summary */1]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */