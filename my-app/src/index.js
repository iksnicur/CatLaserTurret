import express from 'express';
import bodyParser from 'body-parser';
import cors from 'cors';
import axios from 'axios';

const app = express();
const PORT = 80;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// Routes

app.post('/right', (res) => {
    res =  axios.post('http://192.168.190.177:80/right')
});

app.post('/left', (req, res) => {
    res =  axios.post('http://192.168.43.190:80/left')
});

app.post('/up', (req, res) => {
    res =  axios.post('http://192.168.43.190:80/up')
});

app.post('/down', (req, res) => {
    res =  axios.post('http://192.168.43.190:80/down')
});

// app.post('/toggle', (req, res) => {
//     const { count } = req.body;
//     if (typeof count === 'number') {
//         const newCount = count + 1;
//         res.json({ newCount });
//     } else {
//         res.status(400).json({ error: 'Invalid count value' });
//     }
// });

app.get('/camera', (req, res) => {
    res =  axios.post('http://192.168.1.184/camera')
});

app.get('/', (req, res) => {
  res.send('Hello from the server!');
});


// Start server
app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});