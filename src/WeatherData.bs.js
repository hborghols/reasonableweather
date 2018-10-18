// Generated by BUCKLESCRIPT VERSION 4.0.6, PLEASE EDIT WITH CARE
'use strict';

var Json = require("@glennsl/bs-json/src/Json.bs.js");
var Js_exn = require("bs-platform/lib/js/js_exn.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

var url = "https://api.buienradar.nl/data/public/2.0/jsonfeed";

function parseWeatherJson(json) {
  return /* record */[
          /* name */Json_decode.field("stationname", Json_decode.string, json),
          /* summary */Json_decode.field("weatherdescription", Json_decode.string, json),
          /* temp */Json_decode.field("temperature", (function (param) {
                  return Json_decode.optional(Json_decode.$$float, param);
                }), json),
          /* id */String(Json_decode.field("stationid", Json_decode.$$int, json))
        ];
}

function parseWeatherStationsJson(json) {
  return Json_decode.array(parseWeatherJson, json);
}

function parseWeatherResultsJson(json) {
  return Json_decode.at(/* :: */[
                "actual",
                /* :: */[
                  "stationmeasurements",
                  /* [] */0
                ]
              ], parseWeatherStationsJson)(Json.parseOrRaise(json));
}

function getWeather() {
  return fetch(url).then((function (prim) {
                  return prim.text();
                })).then((function (jsonText) {
                var exit = 0;
                var weather;
                try {
                  weather = parseWeatherResultsJson(jsonText);
                  exit = 1;
                }
                catch (raw_e){
                  return Promise.reject(Js_exn.internalToOCamlException(raw_e));
                }
                if (exit === 1) {
                  return Promise.resolve(weather);
                }
                
              }));
}

function parseForecastJson(json) {
  return /* record */[/* summary */Json_decode.field("summary", Json_decode.string, json)];
}

function parseForecastResultJson(json) {
  return Json_decode.at(/* :: */[
                "forecast",
                /* :: */[
                  "weatherreport",
                  /* [] */0
                ]
              ], parseForecastJson)(Json.parseOrRaise(json));
}

function getForecast() {
  return fetch(url).then((function (prim) {
                  return prim.text();
                })).then((function (jsonText) {
                var exit = 0;
                var forecast;
                try {
                  forecast = parseForecastResultJson(jsonText);
                  exit = 1;
                }
                catch (raw_e){
                  return Promise.reject(Js_exn.internalToOCamlException(raw_e));
                }
                if (exit === 1) {
                  return Promise.resolve(forecast);
                }
                
              }));
}

exports.url = url;
exports.parseWeatherJson = parseWeatherJson;
exports.parseWeatherStationsJson = parseWeatherStationsJson;
exports.parseWeatherResultsJson = parseWeatherResultsJson;
exports.getWeather = getWeather;
exports.parseForecastJson = parseForecastJson;
exports.parseForecastResultJson = parseForecastResultJson;
exports.getForecast = getForecast;
/* No side effect */