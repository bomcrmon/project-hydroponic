import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';
import { AngularFireDatabase } from '@angular/fire/compat/database';
import Swal from 'sweetalert2';

@Component({
  selector: 'app-quantity',
  templateUrl: './quantity.component.html',
  styleUrls: ['./quantity.component.css'],
})
export class QuantityComponent implements OnInit {
  Fer: any = 0;
  Mb: any = 0;
  phUp: any = 0;
  phD: any = 0;
  constructor(private auth: AuthService, private db: AngularFireDatabase) {}
  ngOnInit(): void {}

  reset() {
    this.Fer = 0;
    this.Mb = 0;
    this.phUp = 0;
    this.phD = 0;
  }

  async submit() {
    await Swal.fire({
      title: `<b style="color='#000000'" class="fs-3">กดยืนยันเพื่อเติมสารเข้าถังน้ำ</b>`,
      imageUrl: 'assets/icons/delAlert.png',
      reverseButtons: true,
      showCancelButton: true,
      showCloseButton: true,
      confirmButtonColor: '#00C514',
      cancelButtonColor: '#F24E1E',
      confirmButtonText: 'ยืนยัน',
      cancelButtonText: 'ยกเลิก',
      customClass: {
        // actions: 'my-actions',
        cancelButton: 'alert-btn-cancel',
        confirmButton: 'alert-btn-confirm',
      },
    }).then(async (result) => {
      this.auth.Swal('กำลังเติมสารเข้าถังน้ำ', 'success');
      this.db
        .object('quantityFT')
        .set(this.Fer)
        .then(() => console.log('Finish updating value'))
        .catch((error) =>
          console.error('Error updating value in Firebase:', error)
        );

      this.db
        .object('quantityMB')
        .set(this.Mb)
        .then(() => console.log('Finish updating value'))
        .catch((error) =>
          console.error('Error updating value in Firebase:', error)
        );

      this.db
        .object('quantityphup')
        .set(this.phUp)
        .then(() => console.log('Finish updating value'))
        .catch((error) =>
          console.error('Error updating value in Firebase:', error)
        );

      this.db
        .object('quantityphdown')
        .set(this.phD)
        .then(() => console.log('Finish updating value'))
        .catch((error) =>
          console.error('Error updating value in Firebase:', error)
        );
    });
  }

  FT(value: any) {
    if (value === 250) {
      this.Fer = 13;
    } else if (value === 500) {
      this.Fer = 26;
    }
    // else if (value === 750) {
    //   this.Fer = 30;
    // }
    else {
      this.Fer = 0;
    }
    console.log(this.Fer);
  }

  MB(value: any) {
    if (value === 250) {
      this.Mb = 13;
    } else if (value === 500) {
      this.Mb = 26;
    }
    // else if (value === 750) {
    //   this.Mb = 30;
    // }
    else {
      this.Mb = 0;
    }
    console.log(this.Mb);
  }

  PhUp(value: any) {
    if (value === 250) {
      this.phUp = 13;
    } else if (value === 500) {
      this.phUp = 26;
    }
    // else if (value === 750) {
    //   this.phUp = 30;
    // }
    else {
      this.phUp = 0;
    }
    console.log(this.phUp);
  }

  PhD(value: any) {
    if (value === 250) {
      this.phD = 13;
    } else if (value === 500) {
      this.phD = 26;
    }
    // else if (value === 750) {
    //   this.phD = 30;
    // }
    else {
      this.phD = 0;
    }
    console.log(this.phD);
  }
}
