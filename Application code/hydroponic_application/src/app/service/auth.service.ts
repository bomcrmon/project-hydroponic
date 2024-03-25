import { Injectable } from '@angular/core';
import { AngularFireAuth} from '@angular/fire/compat/auth'
import { AngularFireDatabase } from '@angular/fire/compat/database';

import { Router } from '@angular/router';
@Injectable({
  providedIn: 'root'
})
export class AuthService {
  constructor(private fireauth : AngularFireAuth, private router :Router,private db: AngularFireDatabase) { }


  //login
  login(email :string, password: string){
    this.fireauth.signInWithEmailAndPassword(email,password).then( () => {
      localStorage.setItem('token','true');
      this.router.navigate(['home']);
    }, err => {
      alert(err.message);
      this.router.navigate(['/login']);
          })
  }


//register
register(email :string, password: string){
    this.fireauth.createUserWithEmailAndPassword(email,password).then( () => {
      alert('Register Successful')      
      this.router.navigate(['/login']);
    }, err => {
      alert(err.message);
      this.router.navigate(['/register']);
          })
  }


//logout
logout(){
    this.fireauth.signOut().then( () => {
      localStorage.removeItem('token');   
      this.router.navigate(['/login']);
    }, err => {
      alert(err.message);
          })
  }


  //get data มาดู
  humidityValue() {
    return this.db.object('Humidity').valueChanges();
  }
  temperatureValue() {
    return this.db.object('Temperature').valueChanges();
  }
  pHValue() {
    return this.db.object('pHValue').valueChanges();
  }
  fertilizersState() {
    return this.db.object('fertilizersState').valueChanges();
  }
  waterState () {
    return this.db.object('waterState').valueChanges();
  }

}



