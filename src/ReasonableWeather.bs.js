// Generated by BUCKLESCRIPT VERSION 4.0.6, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var WeatherData$ReactTemplate = require("./WeatherData.bs.js");

var component = ReasonReact.reducerComponent("App");

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              WeatherData$ReactTemplate.getWeather(/* () */0).then((function (weather) {
                        Curry._1(self[/* send */3], /* WeatherLoaded */Block.__(0, [weather]));
                        return Promise.resolve(/* () */0);
                      })).catch((function () {
                      Curry._1(self[/* send */3], /* WeatherError */0);
                      return Promise.resolve(/* () */0);
                    }));
              WeatherData$ReactTemplate.getForecast(/* () */0).then((function (forecast) {
                        Curry._1(self[/* send */3], /* ForecastLoaded */Block.__(1, [forecast]));
                        return Promise.resolve(/* () */0);
                      })).catch((function () {
                      Curry._1(self[/* send */3], /* ForecastError */1);
                      return Promise.resolve(/* () */0);
                    }));
              return /* () */0;
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1][/* weather */0];
              var weatherComponent = typeof match === "number" ? (
                  match !== 0 ? "Error loading weather..." : "Loading weather..."
                ) : $$Array.map((function (station) {
                        var match = station[/* name */0];
                        switch (match) {
                          case "Meetstation Groningen" : 
                              var match$1 = station[/* temp */2];
                              return React.createElement("p", {
                                          key: station[/* id */3]
                                        }, React.createElement("a", {
                                              className: "buienradar-link",
                                              href: "https://www.buienradar.nl/weer/groningen/nl/2755251"
                                            }, "Groningen"), ": " + ((
                                            match$1 !== undefined ? Pervasives.string_of_float(match$1) + "C" : "No temp found"
                                          ) + (", " + (station[/* summary */1] + " "))));
                          case "Meetstation Schiphol" : 
                              var match$2 = station[/* temp */2];
                              return React.createElement("p", {
                                          key: station[/* id */3]
                                        }, React.createElement("a", {
                                              className: "buienradar-link",
                                              href: "https://www.buienradar.nl/weer/amsterdam/nl/2759794"
                                            }, "Amsterdam"), ": " + ((
                                            match$2 !== undefined ? Pervasives.string_of_float(match$2) + "C" : "No temp found"
                                          ) + (", " + (station[/* summary */1] + " "))));
                          case "Meetstation Volkel" : 
                              var match$3 = station[/* temp */2];
                              return React.createElement("p", {
                                          key: station[/* id */3]
                                        }, React.createElement("a", {
                                              className: "buienradar-link",
                                              href: "https://www.buienradar.nl/weer/nijmegen/nl/2750053"
                                            }, "Nijmegen"), "/", React.createElement("a", {
                                              className: "buienradar-link",
                                              href: "https://www.buienradar.nl/weer/oss/nl/2749234"
                                            }, "Oss"), ": " + ((
                                            match$3 !== undefined ? Pervasives.string_of_float(match$3) + "C" : "No temp found"
                                          ) + (", " + (station[/* summary */1] + " "))));
                          default:
                            return "";
                        }
                      }), match[0]);
              var match$1 = self[/* state */1][/* forecast */1];
              var forecastComponent = typeof match$1 === "number" ? (
                  match$1 !== 0 ? "Error loading forecast" : "Loading forecast..."
                ) : match$1[0][/* summary */0];
              return React.createElement("div", {
                          className: "App"
                        }, React.createElement("h1", undefined, "Huidig weer:"), React.createElement("p", undefined, weatherComponent), React.createElement("h1", undefined, "Voorspelling: "), React.createElement("p", undefined, forecastComponent), React.createElement("p", undefined, "data van: ", React.createElement("a", {
                                  className: "buienradar-link",
                                  href: "https://www.buienradar.nl"
                                }, "https://www.buienradar.nl")));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* weather : None */0,
                      /* forecast : None */0
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _prevState) {
              if (typeof action === "number") {
                if (action === 0) {
                  return /* Update */Block.__(0, [/* record */[
                              /* weather : Error */1,
                              /* forecast */_prevState[/* forecast */1]
                            ]]);
                } else {
                  return /* Update */Block.__(0, [/* record */[
                              /* weather */_prevState[/* weather */0],
                              /* forecast : Error */1
                            ]]);
                }
              } else if (action.tag) {
                return /* Update */Block.__(0, [/* record */[
                            /* weather */_prevState[/* weather */0],
                            /* forecast : Some */[action[0]]
                          ]]);
              } else {
                return /* Update */Block.__(0, [/* record */[
                            /* weather : Some */[action[0]],
                            /* forecast */_prevState[/* forecast */1]
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */