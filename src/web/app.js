console.log('begin');
feather.replace();

let jsonObject = {};

setInterval(() => {
  getAll();
  updateData(jsonObject);
}, 2000);

const getAll = () => {
  axios.get('/data')
    .then(function (response) {
      jsonObject = response.data;
    });
}

const updateData = (data) => {
  if (Object.keys(data).length) {
    document.getElementById("uptime").innerHTML = data.uptime;
    document.getElementById("ip").innerHTML = data.ipaddr;
    document.getElementById("heap").innerHTML = data.free_heap;
    document.getElementById("cpu").innerHTML = data.cpu;
    document.getElementById("flash").innerHTML = data.flash;
  }
}

const nightClick = () => {
  console.log('hello')
}