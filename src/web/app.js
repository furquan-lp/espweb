console.log('begin');

let jsonObject = {};

setInterval(() => {
  getAll();
  updateData(jsonObject);
}, 2000);

const getAll = () => {
  axios.get('data')
    .then(function (response) {
      console.log(response.data);
      jsonObject = response.data;
    });
}

const updateData = (data) => {
  document.getElementById("uptime").innerHTML = data.uptime;
  document.getElementById("ip").innerHTML = data.ipaddr;
  document.getElementById("heap").innerHTML = data.free_heap;
}