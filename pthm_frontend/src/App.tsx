import { BrowserRouter, Routes, Route } from 'react-router-dom'
import 'bootstrap/dist/css/bootstrap.min.css';
import './App.css'
import { Patient } from './Pages'
import { Sidebar } from './Components'

function App() {

  return (
    <BrowserRouter>
      <Sidebar/>
      <Routes>
        <Route path='/test' element={<Patient/>}/>
      </Routes>
    </BrowserRouter>
  )
}

export default App
