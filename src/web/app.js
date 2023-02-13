console.log('begin');
feather.replace();

const colorsLight = {
  mainBg: '#f1faee',
  mainShadow: '#f1faee',
  mainText: '#1d3557',
  mainLink: '#457b9d',
  mainRed: '#e63946',
  mainLight: '#a8dadc',
  newShadow: '#e5e5e5',
  newBlue: '#219ebc',
  htmlBg: 'white'
};

const colorsDark = {
  mainBg: '#f1faee',
  mainShadow: '#f1faee',
  mainText: '#1d3557',
  mainLink: '#457b9d',
  mainRed: '#e63946',
  mainLight: '#a8dadc',
  newShadow: '#e5e5e5',
  newBlue: '#219ebc',
  htmlBg: 'white'
};

let jsonObject = {};
let nightMode = false;

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
}