import { Injectable } from '@angular/core';
import { AngularFireAuth} from '@angular/fire/compat/auth'
import { AngularFireDatabase } from '@angular/fire/compat/database';

import { Router } from '@angular/router';
@Injectable({
  providedIn: 'root'
})
export class AuthService {
  constructor(private fireauth : AngularFireAuth, private router :Router,private db: AngularFireDatabase) { }
  relaystate_fanRef = this.db.list('relaystate/fan');
  relaystate_ledRef = this.db.list('relaystate/led');

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


  // getSwitchValue(switchKey: string) {
  //   return this.db.object(`relaystate/${switchKey}`).valueChanges();
  // }

  // setSwitchValue(switchKey: string, value: boolean) {
  //   this.db.object(`relaystate/${switchKey}`).set(value);
  // }


  // fan () {
  //   return this.db.object('pHValue').valueChanges();
  // }
  // led () {
  //   return this.db.object('pHValue').valueChanges();
  // }
  // pump_ph_down () {
  //   return this.db.object('pump_ph_down').valueChanges();
  // }
  // pump_ph_up () {
  //   return this.db.object('pump_ph_up').valueChanges();
  // }
  // pump_water_up () {
  //   return this.db.object('pump_water_up').valueChanges();
  // }
  // sprinklerfertilizers () {
  //   return this.db.object('sprinklerfertilizers').valueChanges();
  // }
  // sprinklerwater () {
  //   return this.db.object('sprinklerwater').valueChanges();
  // }


}



