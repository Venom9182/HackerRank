import React from 'react';
import './App.css';
import { Switch, Route, Redirect } from 'react-router-dom';
import Login from './login/Login';
import Home from './userDashBoard/Home';
import { Button } from '@mui/material';
import Otp from './login/Otp';
import ContactFormModal from './login/ContactFormModal';



const App=()=> {
  const [loginUser,setLoginUser]=React.useState(false);
  const [userType,setUserType]=React.useState('');


  React.useEffect(()=>{
      console.log("hello");
      },[loginUser,userType]);


  const toggleLogin=((ele)=>{
      setLoginUser(ele);
  });
  
  const toggleUser=((ele)=>{
    setUserType(ele);
});

  return (
    <>
    <Switch>
        <Route path='/login' exact component={props => <Login {...props} toggleLogin={toggleLogin} toggleUser={toggleUser} />} />
        <Route path ="/contact" component={ContactFormModal} />
    {loginUser ? <Home toggleLogin={toggleLogin} toggleUser={toggleUser} userType={userType}/> : <Redirect to={{pathname:"/login"}}/>}
    </Switch>
    </>
    
  );
}

export default App;
