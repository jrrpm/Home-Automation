var request = require('request');

var hue = new function() {

    var tUser = "xMjcTqqAixNzXCaY51G6IUhVyB1lCeam-JppPTkL";
    var aUrl = "http://192.168.1.11/api/";
    var eLog = false;
    var colorMedium = 13109;
    var colorHigh = 33016;
    var lightsID = [1,2,3];

    function sendRequest(command, params)
    {
        request({
            url: aUrl+tUser+command,
            method: 'PUT',
            json: params
        }, function(err, response) {
            if (eLog) {
                if (err) console.log(err);
                else console.log(response.body);
            }
      });
    }

    this.allLightsOff = function() {
        if (eLog) console.log("philips off");
        var json = {
            "on": false
        };
        for (var i in lightsID) sendRequest("/lights/"+lightsID[i]+"/state", json);
    }

    this.allLightsOn = function() {
        if (eLog) console.log("philips on");
        var json = {
            "on": true,
            "bri": 254,
            "hue": colorHigh,
            "sat": 254
        };
        for (var i in lightsID) sendRequest("/lights/"+lightsID[i]+"/state", json);
    }

    this.allLightsBright = function(value) {
        if (eLog) console.log("philips bright:" + value);
        var json = {
            "on": true,
            "bri": value,
            "hue": colorMedium,
            "sat": 254
        };
        for (var i in lightsID) sendRequest("/lights/"+lightsID[i]+"/state", json);
    }

};

module.exports = hue;
