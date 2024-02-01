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
  relaystate_fertilizers = this.db.list('relaystate/fertilizers');
  relaystate_ledRef = this.db.list('relaystate/led');
  relaystate_microbialRef = this.db.list('relaystate/microbial');
  relaystate_pumpStirring = this.db.list('relaystate/pumpStirring');
  relaystate_pumpUP = this.db.list('relaystate/pumpUP');
  relaystate_pumpphDown = this.db.list('relaystate/pumpphDown');
  relaystate_pumpphUP = this.db.list('relaystate/pumpphUP');
  relaystate_pumpwater = this.db.list('relaystate/pumpwater');
  relaystate_sprinklerfertilizers = this.db.list('relaystate/sprinklerfertilizers');
  relaystate_sprinklerwater = this.db.list('relaystate/sprinklerwater');
  relaystate_valve = this.db.list('relaystate/valve');

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



