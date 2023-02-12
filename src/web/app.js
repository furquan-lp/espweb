console.log('begin');

let jsonObject = {};

setInterval(() => {
  getAll();
  updateData(jsonObject);
}, 2000);

const getAll = () => {
  axios.get('http://192.168.0.8/data')
    .then(function (response) {
      console.log(response.data);
      jsonObject = response.data;
    });
}

const updateData = (data) => {
  document.getElementById("uptime").innerHTML = data.uptime;
  document.getElementById("ip").innerHTML = data.ipaddr;
  document.getElementById("heap").innerHTML = data.free_heap;
  document.getElementById("cpu").innerHTML = data.cpu;
  document.getElementById("flash").innerHTML = data.flash;
}