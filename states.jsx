const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    // You can use the 'username' and 'password' states here for further processing
    console.log('Username:', username);
    console.log('Password:', password);
    // You can also perform API requests or other actions here
  };
