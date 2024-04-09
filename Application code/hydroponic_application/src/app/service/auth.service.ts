import { Injectable } from '@angular/core';
import { AngularFireAuth} from '@angular/fire/compat/auth'
import { AngularFireDatabase } from '@angular/fire/compat/database';
import { Router } from '@angular/router';
import { environment } from 'src/environments/environment.development';
import Swal from 'sweetalert2';
import { AlertComponent } from '../outlet/alert/alert.component';
import {
  MatDialog,
  MatDialogRef,
  MAT_DIALOG_DATA,
} from '@angular/material/dialog';


@Injectable({
  providedIn: 'root'
})
export class AuthService {
  constructor(private fireauth : AngularFireAuth, private router :Router,private db: AngularFireDatabase,private dialog: MatDialog) { }


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
  waterStateLow() {
    return this.db.object('waterstatelow').valueChanges();
  }
  waterStateHigh () {
    return this.db.object('waterstatehigh').valueChanges();
  }


  async Swal(title: any, icon: any, text = '', callback = '', color = '') {
    await Swal.fire({
      title: `<b style="color:${color};" class="fs-3">${title}</b>`,
      text: text,
      confirmButtonText: 'ตกลง',
      confirmButtonColor: '#19c82a',
      showConfirmButton: true,
      showCloseButton: true,
      icon: icon,
      customClass: {
        // actions: 'my-actions',
        cancelButton: 'reset',
        confirmButton: 'submit',
      },
    }).then((result:any) => {
      if (callback) {
        window.location.href = `./${callback}`;
      }
    });
  }

  alertPopUp({
    title='',
    text='',
    status='',
    redirectLink = null,
    textButton = 'เสร็จสิ้น',
    cancleButton = false,
    confirmButton = false,
    cancleButtonText = 'ยกเลิก',
    width = 40,
  }) {
    const dialogRef = this.dialog.open(AlertComponent, {
      width: `${width}vw`,
      autoFocus: false,
      disableClose: true,
    });

    dialogRef.componentInstance.data = {
      title: title,
      text: text,
      status: status,
      textButton: textButton,
      cancleButton: cancleButton,
      confirmButton: confirmButton,
      cancleButtonText: cancleButtonText,
    };

    dialogRef.afterClosed().subscribe(async (result) => {
      if (result.isResult) {
        if (redirectLink) {
          window.location.href = `./${redirectLink}`;
        }
      }
    });
  }

}



