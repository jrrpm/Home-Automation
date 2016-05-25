var hue = require('../lib/philipshue.js');

module.exports = function(Cloudbit) {

    var lightbits = "243c200e2bab";
    var rollerbits = "";
    var hueRangeTop = 98;
    var hueRangeBot = 84;
    var eLog = false;

    Cloudbit.receive = function(data, cb) { 
        if (eLog) console.log(data);
        var payload = data.payload;
        if (data.bit_id==lightbits && payload.delta=='amplitude:level:active') //lightbits process hue
        {
                var percent = parseInt(payload.percent);
                if (eLog) console.log("percent: " + percent);
                if (percent<hueRangeBot) hue.allLightsOff();
                else if (percent>hueRangeTop) hue.allLightsOn();
                else {    //change bright
                    var range = hueRangeTop - hueRangeBot;
                    if (eLog) console.log("range: " + range);
                    var value = percent - hueRangeTop + range;
                    value = Math.round((value/range)*255);
                    hue.allLightsBright(value);
                }
        }
        cb(null, "OK");
    };

    Cloudbit.remoteMethod(
        'receive',
        {
            accepts: { arg: 'data', type: 'object', http: { source: 'body' } },
            returns: {arg: 'fresp', type: 'string'},
            http: {path:'/receive', verb: 'post'}
        }
    );
};
